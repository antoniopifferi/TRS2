#include "AppLogger.h"

#include <QObject>
#include <QString>
#include <QMessageBox>
#include <QCoreApplication>
#include <QThread>
#include <QMetaObject>
#include <QInputDialog>
#include <QLineEdit>
#include <QByteArray>

#include <algorithm>
#include <cstring>
#include <iostream>

class AppLogger : public QObject {
    Q_OBJECT
public:
    static AppLogger& instance() { static AppLogger i; return i; }
    void log(const QString& m) { emit message(m); }
    void panel(const QString& p) { emit showPanel(p); }
signals:
    void message(const QString& msg);
    void showPanel(const QString& panelName);
private:
    AppLogger() = default;
    Q_DISABLE_COPY(AppLogger)
};

static QString qstr_from_std(const std::string& s) { return QString::fromUtf8(s.c_str(), static_cast<int>(s.size())); }

QObject* AppLoggerObject() { return &AppLogger::instance(); }

// C linkage wrappers
extern "C" {
    void outText_c(const char* s) {
        if (!s) return;
        AppLogger::instance().log(QString::fromUtf8(s));
    }

    void ErrHandler_c(const char* device, int code, const char* message) {
        const QString dev = device ? QString::fromUtf8(device) : QString();
        const QString msg = message ? QString::fromUtf8(message) : QString();
        AppLogger::instance().log(msg);
        if (code) AppLogger::instance().panel(QStringLiteral("Errors"));
        // also show modal on UI thread
        auto show = [dev, msg]() {
            QMessageBox m; m.setIcon(QMessageBox::Critical); m.setWindowTitle(QStringLiteral("Error"));
            m.setText(msg); m.setStandardButtons(QMessageBox::Ok); m.setWindowModality(Qt::ApplicationModal); m.exec();
        };
        if (auto app = QCoreApplication::instance(); app && QThread::currentThread() != app->thread())
            QMetaObject::invokeMethod(app, show, Qt::BlockingQueuedConnection);
        else
            show();
    }

    bool askYesNo_c(const char* title, const char* text) {
        bool result = false;
        auto runner = [&]() {
            auto btn = QMessageBox::question(nullptr, QString::fromUtf8(title ? title : ""), QString::fromUtf8(text ? text : ""), QMessageBox::Yes | QMessageBox::No);
            result = (btn == QMessageBox::Yes);
        };
        if (auto app = QCoreApplication::instance(); app && QThread::currentThread() != app->thread()) {
            QMetaObject::invokeMethod(app, runner, Qt::BlockingQueuedConnection);
        } else runner();
        return result;
    }

    bool getTextInput_c(const char* title, const char* label, char* outBuf, int outBufLen) {
        bool ok = false;
        auto runner = [&]() {
            bool okLocal = false;
            QString initial = outBuf && outBufLen > 0 ? QString::fromUtf8(outBuf) : QString();
            QString text = QInputDialog::getText(nullptr, QString::fromUtf8(title ? title : ""), QString::fromUtf8(label ? label : ""), QLineEdit::Normal, initial, &okLocal);
            if (okLocal) {
                QByteArray ba = text.toUtf8();
                const int len = std::min(outBufLen - 1, static_cast<int>(ba.size()));
                memcpy(outBuf, ba.constData(), len);
                outBuf[len] = '\0';
                ok = true;
            }
        };
        if (auto app = QCoreApplication::instance(); app && QThread::currentThread() != app->thread()) {
            QMetaObject::invokeMethod(app, runner, Qt::BlockingQueuedConnection);
        } else runner();
        return ok;
    }

    void showPanel_c(const char* name) {
        if (!name) return;
        AppLogger::instance().panel(QString::fromUtf8(name));
    }
}

void runOnUiThread(const std::function<void()>& fn)
{
    if (auto app = QCoreApplication::instance(); app && QThread::currentThread() != app->thread()) {
        QMetaObject::invokeMethod(app, fn, Qt::BlockingQueuedConnection);
    }
    else {
        fn();
    }
}

#include "AppLogger.moc"
