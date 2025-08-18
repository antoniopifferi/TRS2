#pragma once

// ==========================
// Binder.h (Qt6, header-only)
// ==========================

#include <QObject>
#include <QWidget>
#include <QPointer>
#include <QSignalBlocker>

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>

#include <QSettings>
#include <QHash>
#include <QHashFunctions>
#include <QString>
#include <QStringView>

#include <unordered_map>
#include <vector>
#include <memory>
#include <type_traits>
#include <string>
#include <algorithm> // clamp

namespace qtbind {

    // Hash functor for QString to use in std::unordered_map
    struct QStringHash {
        std::size_t operator()(const QString& s) const noexcept {
            return static_cast<std::size_t>(qHash(s));
        }
    };

    // ---------------------------------------------
    // Binder: find-by-objectName, two-way data-bind
    // ---------------------------------------------
    class Binder {
    public:
        explicit Binder(QObject* root) : m_root(root) {}

        // Bind by designer objectName to your variable reference.
        // Returns true on success (supported widget + found), false otherwise.
        template <typename T>
        bool bind(const QString& objectName, T& var) {
            if (!m_root) return false;

            QWidget* w = lookup(objectName);
            if (!w) return false;

            std::unique_ptr<IBinding> b;

            // Try supported widgets. Only the matching (widget,type) pair returns non-null
            if (!b) { if (auto* sb = qobject_cast<QSpinBox*>(w))         b = makeBinding(sb, var); }
            if (!b) { if (auto* ds = qobject_cast<QDoubleSpinBox*>(w))   b = makeBinding(ds, var); }
            if (!b) { if (auto* le = qobject_cast<QLineEdit*>(w))        b = makeBinding(le, var); }
            if (!b) { if (auto* ck = qobject_cast<QCheckBox*>(w))        b = makeBinding(ck, var); }
            if (!b) { if (auto* cb = qobject_cast<QComboBox*>(w))        b = makeBinding(cb, var); }

            if (!b) return false;

            const QString key = objectName;
            m_bindings[key].push_back(std::move(b));          // std::vector<unique_ptr<...>>
            m_widgetByName.insert(key, QPointer<QWidget>(w)); // safe, copyable
            return true;
        }

        // -------- Bulk sync --------

        // widgets -> variables
        bool readAll() {
            bool ok = true;
            for (auto& [name, vec] : m_bindings) {
                for (auto& b : vec) ok &= b->pull();
            }
            return ok;
        }

        // variables -> widgets
        bool writeAll() {
            bool ok = true;
            for (auto& [name, vec] : m_bindings) {
                // push preferred binding first (e.g., QComboBox index over text)
                int preferred = findPreferredIndex(vec);
                if (preferred >= 0) ok &= vec[preferred]->push();
                for (int i = 0; i < static_cast<int>(vec.size()); ++i) {
                    if (i == preferred) continue;
                    ok &= vec[i]->push();
                }
            }
            return ok;
        }

        // -------- Single sync by objectName --------

        bool readSingle(const QString& objectName) {
            auto it = m_bindings.find(objectName);
            if (it == m_bindings.end()) return false;
            bool ok = true;
            for (auto& b : it->second) ok &= b->pull();
            return ok;
        }

        bool writeSingle(const QString& objectName) {
            auto it = m_bindings.find(objectName);
            if (it == m_bindings.end()) return false;
            bool ok = true;
            int preferred = findPreferredIndex(it->second);
            if (preferred >= 0) ok &= it->second[preferred]->push();
            for (int i = 0; i < static_cast<int>(it->second.size()); ++i) {
                if (i == preferred) continue;
                ok &= it->second[i]->push();
            }
            return ok;
        }

        // -------- Settings: INI --------

        void saveIni(const QString& filePath) const {
            QSettings s(filePath, QSettings::IniFormat);
            saveToSettings(s);
            s.sync();
        }

        void loadIni(const QString& filePath) {
            QSettings s(filePath, QSettings::IniFormat);
            loadFromSettings(s);
        }

        void saveToSettings(QSettings& s) const {
            forEachLiveWidget([&](const QString& name, QWidget* w) {
                saveWidget(s, name, w);
                });
        }

        void loadFromSettings(QSettings& s) {
            forEachLiveWidget([&](const QString& name, QWidget* w) {
                loadWidget(s, name, w);
                });
            // Bindings are signal-connected, so variables update automatically
        }

        bool hasBinding(const QString& objectName) const {
            auto it = m_widgetByName.find(objectName);
            return it != m_widgetByName.end() && !it.value().isNull();
        }

    private:
        // ---------------- Binding core types ----------------

        struct IBinding {
            virtual ~IBinding() = default;
            virtual const QString& name() const = 0;
            virtual QWidget* widget() const = 0;
            virtual bool pull() = 0; // widget -> var
            virtual bool push() = 0; // var -> widget
            virtual bool isPreferredForPush() const { return false; }
        };

        template <typename T, typename W>
        class BaseBinding : public IBinding {
        public:
            BaseBinding(const QString& n, W* w, T& varRef)
                : name_(n), widget_(w), var_(&varRef) {
            }

            const QString& name() const override { return name_; }
            QWidget* widget() const override { return widget_.data(); }

        protected:
            QString name_;
            QPointer<W> widget_;
            T* var_;
        };

        // ---------------- makeBinding overloads ----------------

        // QSpinBox <-> int OR long / long long
        template <typename T>
        static std::unique_ptr<IBinding> makeBinding(QSpinBox* w, T& var) {
            if constexpr (std::is_same_v<T, int>) {
                struct B final : BaseBinding<int, QSpinBox> {
                    using Base = BaseBinding<int, QSpinBox>;
                    B(const QString& n, QSpinBox* w, int& v) : Base(n, w, v) {
                        if (w) {
                            if (this->var_) *this->var_ = w->value();
                            QObject::connect(w, QOverload<int>::of(&QSpinBox::valueChanged),
                                w, [ptr = this->var_](int v) { if (ptr) *ptr = v; },
                                Qt::UniqueConnection);
                        }
                    }
                    bool pull() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        *this->var_ = w->value(); return true;
                    }
                    bool push() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        QSignalBlocker b(w); w->setValue(*this->var_); return true;
                    }
                };
                return std::make_unique<B>(w->objectName(), w, var);

            }
            else if constexpr (std::is_same_v<T, long> || std::is_same_v<T, long long>) {
                struct B final : BaseBinding<T, QSpinBox> {
                    using Base = BaseBinding<T, QSpinBox>;
                    B(const QString& n, QSpinBox* w, T& v) : Base(n, w, v) {
                        if (w) {
                            if (this->var_) *this->var_ = static_cast<T>(w->value());
                            QObject::connect(w, QOverload<int>::of(&QSpinBox::valueChanged),
                                w, [ptr = this->var_](int iv) { if (ptr) *ptr = static_cast<T>(iv); },
                                Qt::UniqueConnection);
                        }
                    }
                    bool pull() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        *this->var_ = static_cast<T>(w->value()); return true;
                    }
                    bool push() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        QSignalBlocker b(w);
                        auto v = *this->var_;
                        if (v < static_cast<T>(w->minimum())) v = static_cast<T>(w->minimum());
                        if (v > static_cast<T>(w->maximum())) v = static_cast<T>(w->maximum());
                        w->setValue(static_cast<int>(v)); return true;
                    }
                };
                return std::make_unique<B>(w->objectName(), w, var);

            }
            else {
                return nullptr;
            }
        }

        // QDoubleSpinBox <-> double  (and integral types by conversion)
        template <typename T>
        static std::unique_ptr<IBinding> makeBinding(QDoubleSpinBox* w, T& var) {
            if constexpr (std::is_same_v<T, double>) {
                struct B final : BaseBinding<double, QDoubleSpinBox> {
                    using Base = BaseBinding<double, QDoubleSpinBox>;
                    B(const QString& n, QDoubleSpinBox* w, double& v) : Base(n, w, v) {
                        if (w) {
                            if (this->var_) *this->var_ = w->value();
                            QObject::connect(w, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                                w, [ptr = this->var_](double dv) { if (ptr) *ptr = dv; },
                                Qt::UniqueConnection);
                        }
                    }
                    bool pull() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        *this->var_ = w->value(); return true;
                    }
                    bool push() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        QSignalBlocker b(w); w->setValue(*this->var_); return true;
                    }
                };
                return std::make_unique<B>(w->objectName(), w, var);

            }
            else if constexpr (std::is_integral_v<T> && !std::is_same_v<T, bool>) {
                struct B final : BaseBinding<T, QDoubleSpinBox> {
                    using Base = BaseBinding<T, QDoubleSpinBox>;
                    B(const QString& n, QDoubleSpinBox* w, T& v) : Base(n, w, v) {
                        if (w) {
                            if (this->var_) *this->var_ = static_cast<T>(w->value());
                            QObject::connect(w, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                                w, [ptr = this->var_](double dv) { if (ptr) *ptr = static_cast<T>(dv); },
                                Qt::UniqueConnection);
                        }
                    }
                    bool pull() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        *this->var_ = static_cast<T>(w->value()); return true;
                    }
                    bool push() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        QSignalBlocker b(w); w->setValue(static_cast<double>(*this->var_)); return true;
                    }
                };
                return std::make_unique<B>(w->objectName(), w, var);

            }
            else {
                return nullptr;
            }
        }

        // QLineEdit <-> QString OR std::string
        template <typename T>
        static std::unique_ptr<IBinding> makeBinding(QLineEdit* w, T& var) {
            if constexpr (std::is_same_v<T, QString>) {
                struct B final : BaseBinding<QString, QLineEdit> {
                    using Base = BaseBinding<QString, QLineEdit>;
                    B(const QString& n, QLineEdit* w, QString& v) : Base(n, w, v) {
                        if (w) {
                            if (this->var_) *this->var_ = w->text();
                            QObject::connect(w, &QLineEdit::textChanged, w,
                                [ptr = this->var_](const QString& t) { if (ptr) *ptr = t; },
                                Qt::UniqueConnection);
                        }
                    }
                    bool pull() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        *this->var_ = w->text(); return true;
                    }
                    bool push() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        QSignalBlocker b(w); w->setText(*this->var_); return true;
                    }
                };
                return std::make_unique<B>(w->objectName(), w, var);

            }
            else if constexpr (std::is_same_v<T, std::string>) {
                struct B final : BaseBinding<std::string, QLineEdit> {
                    using Base = BaseBinding<std::string, QLineEdit>;
                    B(const QString& n, QLineEdit* w, std::string& v) : Base(n, w, v) {
                        if (w) {
                            if (this->var_) *this->var_ = w->text().toStdString();
                            QObject::connect(w, &QLineEdit::textChanged, w,
                                [ptr = this->var_](const QString& t) { if (ptr) *ptr = t.toStdString(); },
                                Qt::UniqueConnection);
                        }
                    }
                    bool pull() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        *this->var_ = w->text().toStdString(); return true;
                    }
                    bool push() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        QSignalBlocker b(w); w->setText(QString::fromStdString(*this->var_)); return true;
                    }
                };
                return std::make_unique<B>(w->objectName(), w, var);

            }
            else {
                return nullptr;
            }
        }

        // QCheckBox <-> bool (and integral T as 0/1)
        template <typename T>
        static std::unique_ptr<IBinding> makeBinding(QCheckBox* w, T& var) {
            if constexpr (std::is_same_v<T, bool>) {
                struct B final : BaseBinding<bool, QCheckBox> {
                    using Base = BaseBinding<bool, QCheckBox>;
                    B(const QString& n, QCheckBox* w, bool& v) : Base(n, w, v) {
                        if (w) {
                            if (this->var_) *this->var_ = w->isChecked();
                            QObject::connect(w, &QCheckBox::toggled, w,
                                [ptr = this->var_](bool b) { if (ptr) *ptr = b; },
                                Qt::UniqueConnection);
                        }
                    }
                    bool pull() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        *this->var_ = w->isChecked(); return true;
                    }
                    bool push() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        QSignalBlocker b(w); w->setChecked(*this->var_); return true;
                    }
                };
                return std::make_unique<B>(w->objectName(), w, var);

            }
            else if constexpr (std::is_integral_v<T>) {
                struct B final : BaseBinding<T, QCheckBox> {
                    using Base = BaseBinding<T, QCheckBox>;
                    B(const QString& n, QCheckBox* w, T& v) : Base(n, w, v) {
                        if (w) {
                            if (this->var_) *this->var_ = w->isChecked() ? T{ 1 } : T{ 0 };
                            QObject::connect(w, &QCheckBox::toggled, w,
                                [ptr = this->var_](bool b) { if (ptr) *ptr = b ? T{ 1 } : T{ 0 }; },
                                Qt::UniqueConnection);
                        }
                    }
                    bool pull() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        *this->var_ = w->isChecked() ? T{ 1 } : T{ 0 }; return true;
                    }
                    bool push() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        QSignalBlocker b(w); w->setChecked(*this->var_ != 0); return true;
                    }
                };
                return std::make_unique<B>(w->objectName(), w, var);

            }
            else {
                return nullptr;
            }
        }

        // QComboBox <-> int (index) OR QString/std::string (text)
        template <typename T>
        static std::unique_ptr<IBinding> makeBinding(QComboBox* w, T& var) {
            if constexpr (std::is_same_v<T, int>) {
                struct B final : BaseBinding<int, QComboBox> {
                    using Base = BaseBinding<int, QComboBox>;
                    B(const QString& n, QComboBox* w, int& v) : Base(n, w, v) {
                        if (w) {
                            if (this->var_) *this->var_ = w->currentIndex();
                            QObject::connect(w, QOverload<int>::of(&QComboBox::currentIndexChanged), w,
                                [ptr = this->var_](int i) { if (ptr) *ptr = i; },
                                Qt::UniqueConnection);
                        }
                    }
                    bool pull() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        *this->var_ = w->currentIndex(); return true;
                    }
                    bool push() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        QSignalBlocker b(w); w->setCurrentIndex(*this->var_); return true;
                    }
                    bool isPreferredForPush() const override { return true; } // prefer index when both bound
                };
                return std::make_unique<B>(w->objectName(), w, var);

            }
            else if constexpr (std::is_same_v<T, QString>) {
                struct B final : BaseBinding<QString, QComboBox> {
                    using Base = BaseBinding<QString, QComboBox>;
                    B(const QString& n, QComboBox* w, QString& v) : Base(n, w, v) {
                        if (w) {
                            if (this->var_) *this->var_ = w->currentText();
                            QObject::connect(w, &QComboBox::currentTextChanged, w,
                                [ptr = this->var_](const QString& t) { if (ptr) *ptr = t; },
                                Qt::UniqueConnection);
                        }
                    }
                    bool pull() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        *this->var_ = w->currentText(); return true;
                    }
                    bool push() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        QSignalBlocker b(w); w->setCurrentText(*this->var_); return true;
                    }
                };
                return std::make_unique<B>(w->objectName(), w, var);

            }
            else if constexpr (std::is_same_v<T, std::string>) {
                struct B final : BaseBinding<std::string, QComboBox> {
                    using Base = BaseBinding<std::string, QComboBox>;
                    B(const QString& n, QComboBox* w, std::string& v) : Base(n, w, v) {
                        if (w) {
                            if (this->var_) *this->var_ = w->currentText().toStdString();
                            QObject::connect(w, &QComboBox::currentTextChanged, w,
                                [ptr = this->var_](const QString& t) { if (ptr) *ptr = t.toStdString(); },
                                Qt::UniqueConnection);
                        }
                    }
                    bool pull() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        *this->var_ = w->currentText().toStdString(); return true;
                    }
                    bool push() override {
                        auto* w = this->widget_.data(); if (!w || !this->var_) return false;
                        QSignalBlocker b(w); w->setCurrentText(QString::fromStdString(*this->var_)); return true;
                    }
                };
                return std::make_unique<B>(w->objectName(), w, var);

            }
            else {
                return nullptr;
            }
        }

        // ---------------- Settings helpers ----------------

        static void saveWidget(QSettings& s, const QString& name, QWidget* w) {
            if (auto* sb = qobject_cast<QSpinBox*>(w)) {
                s.setValue(name + "/value", sb->value());
            }
            else if (auto* ds = qobject_cast<QDoubleSpinBox*>(w)) {
                s.setValue(name + "/value", ds->value());
            }
            else if (auto* le = qobject_cast<QLineEdit*>(w)) {
                s.setValue(name + "/text", le->text());
            }
            else if (auto* ck = qobject_cast<QCheckBox*>(w)) {
                s.setValue(name + "/checked", ck->isChecked());
            }
            else if (auto* cb = qobject_cast<QComboBox*>(w)) {
                s.setValue(name + "/index", cb->currentIndex());
                s.setValue(name + "/text", cb->currentText());
            }
        }

        static void loadWidget(QSettings& s, const QString& name, QWidget* w) {
            if (auto* sb = qobject_cast<QSpinBox*>(w)) {
                if (s.contains(name + "/value")) {
                    QSignalBlocker b(sb);
                    sb->setValue(s.value(name + "/value").toInt());
                }
            }
            else if (auto* ds = qobject_cast<QDoubleSpinBox*>(w)) {
                if (s.contains(name + "/value")) {
                    QSignalBlocker b(ds);
                    ds->setValue(s.value(name + "/value").toDouble());
                }
            }
            else if (auto* le = qobject_cast<QLineEdit*>(w)) {
                if (s.contains(name + "/text")) {
                    QSignalBlocker b(le);
                    le->setText(s.value(name + "/text").toString());
                }
            }
            else if (auto* ck = qobject_cast<QCheckBox*>(w)) {
                if (s.contains(name + "/checked")) {
                    QSignalBlocker b(ck);
                    ck->setChecked(s.value(name + "/checked").toBool());
                }
            }
            else if (auto* cb = qobject_cast<QComboBox*>(w)) {
                if (s.contains(name + "/index")) {
                    QSignalBlocker b(cb);
                    cb->setCurrentIndex(s.value(name + "/index").toInt());
                }
                else if (s.contains(name + "/text")) {
                    QSignalBlocker b(cb);
                    cb->setCurrentText(s.value(name + "/text").toString());
                }
            }
        }

        // ---------------- Lookup / helpers ----------------

        QWidget* lookup(const QString& name) {
            if (auto it = m_widgetByName.find(name); it != m_widgetByName.end()) {
                if (!it.value().isNull()) return it.value();
            }
            QWidget* w = m_root->findChild<QWidget*>(name, Qt::FindChildrenRecursively);
            if (w) m_widgetByName.insert(name, QPointer<QWidget>(w));
            return w;
        }

        template <typename F>
        void forEachLiveWidget(F&& f) const {
            for (auto it = m_widgetByName.begin(); it != m_widgetByName.end(); ++it) {
                if (!it.value().isNull()) f(it.key(), it.value());
            }
        }

        static int findPreferredIndex(const std::vector<std::unique_ptr<IBinding>>& vec) {
            for (int i = 0; i < static_cast<int>(vec.size()); ++i) {
                if (vec[i]->isPreferredForPush()) return i;
            }
            return -1;
        }

    private:
        QObject* m_root = nullptr;

        // objectName -> bindings on that widget
        std::unordered_map<
            QString,
            std::vector<std::unique_ptr<IBinding>>,
            QStringHash
        > m_bindings;

        // objectName -> live widget pointer (destroy-safe)
        QHash<QString, QPointer<QWidget>> m_widgetByName;
    };

    // Convenience macro to avoid typing quotes around objectName tokens
#define QT_BIND(binder, widgetNameToken, varRef) \
    (binder).bind(QStringLiteral(#widgetNameToken), (varRef))

} // namespace qtbind
