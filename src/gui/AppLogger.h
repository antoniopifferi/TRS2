#pragma once
#include <QObject>
#include <QString>
#include <string>
#include <QMessageBox>
#include <QCoreApplication>
#include <QThread>

class AppLogger : public QObject {
    Q_OBJECT
public: static AppLogger& instance() { static AppLogger i; return i; }
    void log(const QString& m) { emit message(m); }
    void panel(const QString& p) { emit showPanel(p); }
signals:
    void message(const QString& msg);
    void showPanel(const QString& panelName);
private: AppLogger() = default; Q_DISABLE_COPY(AppLogger)
};

// Tiny converters
inline QString qstr(const char* s) { return s ? QString::fromUtf8(s) : QString(); }
inline QString qstr(const std::string& s) { return QString::fromUtf8(s.c_str(), static_cast<int>(s.size())); }

// Core implementation
inline void ErrHandlerImpl(const QString& dev, int code, const QString& func, const QString& msg)
{
    const QString d = dev.isEmpty() ? QStringLiteral("UNKNOWN") : dev;
    const QString composed = func.isEmpty()
        ? QStringLiteral("Device = %1\nMessage = %2").arg(d, msg)
        : QStringLiteral("Device = %1\nFunction = %2\nMessage = %3").arg(d, func, msg);

    AppLogger::instance().log(composed);
    if (code) AppLogger::instance().panel(QStringLiteral("Errors"));

    auto show = [c = composed]() {
        QMessageBox m; m.setIcon(QMessageBox::Critical); m.setWindowTitle(QStringLiteral("Error"));
        m.setText(c); m.setStandardButtons(QMessageBox::Ok); m.setWindowModality(Qt::ApplicationModal); m.exec();
    };
    if (auto app = QCoreApplication::instance(); app && QThread::currentThread() != app->thread())
        QMetaObject::invokeMethod(app, std::move(show), Qt::BlockingQueuedConnection);
    else
        show();
}

// Public API helpers
inline void outText(const std::string& s) { AppLogger::instance().log(QString::fromUtf8(s.data(), static_cast<int>(s.size()))); }
inline void displayPanel(const QString& name) { AppLogger::instance().panel(name); }

// User-facing overloads (compact wrappers)
inline void ErrHandler(const QString& Device, int Code, const QString& Function, const QString& Message) { ErrHandlerImpl(Device, Code, Function, Message); }
inline void ErrHandler(const QString& Device, int Code, const QString& Message) { ErrHandlerImpl(Device, Code, QString(), Message); }
inline void ErrHandler(const char* Device, int Code, const char* Function, const char* Message) { ErrHandlerImpl(qstr(Device), Code, qstr(Function), qstr(Message)); }
inline void ErrHandler(const char* Device, int Code, const char* Message) { ErrHandlerImpl(qstr(Device), Code, QString(), qstr(Message)); }
inline void ErrHandler(const std::string& Device, int Code, const std::string& Function, const std::string& Message) { ErrHandlerImpl(qstr(Device), Code, qstr(Function), qstr(Message)); }
inline void ErrHandler(const std::string& Device, int Code, const std::string& Message) { ErrHandlerImpl(qstr(Device), Code, QString(), qstr(Message)); }