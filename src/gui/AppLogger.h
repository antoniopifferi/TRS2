#pragma once
#include <QObject>
#include <QString>
#include <string>

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

// Public API: accept std::string (UTF-8)
inline void outText(const std::string& s) {
    AppLogger::instance().log(QString::fromUtf8(s.data(), static_cast<int>(s.size())));
}

// Public API: switch GUI panel by name (QString only)
inline void displayPanel(const QString& name) {
    AppLogger::instance().panel(name);
}

// --- Minimal and simple error helper (single-file) ---
// Simplest replacement of legacy ErrHandler using device name as string.
inline void ErrHandler(const char* Device, int Code, const char* Function, const char* Message)
{
    const QString sdevice = Device ? QString::fromUtf8(Device) : QStringLiteral("UNKNOWN");
    const QString sfunc   = Function ? QString::fromUtf8(Function) : QString();
    const QString smsg    = Message ? QString::fromUtf8(Message) : QStringLiteral("" );

    const QString composed = QStringLiteral("Device = %1\nFunction = %2\nMessage = %3")
                                 .arg(sdevice, sfunc, smsg);
    AppLogger::instance().log(composed);
    if (Code != 0)
        AppLogger::instance().panel(QStringLiteral("Errors"));
}

// Minimal three-argument overload for single-line usage: ErrHandler("DEV", code, message)
inline void ErrHandler(const char* Device, int Code, const char* Message)
{
    const QString sdevice = Device ? QString::fromUtf8(Device) : QStringLiteral("UNKNOWN");
    const QString smsg    = Message ? QString::fromUtf8(Message) : QStringLiteral("");
    const QString composed = QStringLiteral("Device = %1\nMessage = %2").arg(sdevice, smsg);
    AppLogger::instance().log(composed);
    if (Code != 0)
        AppLogger::instance().panel(QStringLiteral("Errors"));
}

// Convenience overloads
inline void ErrHandler(const QString& Device, int Code, const QString& Function, const QString& Message)
{
    ErrHandler(Device.toUtf8().constData(), Code,
               Function.toUtf8().constData(), Message.toUtf8().constData());
}
inline void ErrHandler(const std::string& Device, int Code, const std::string& Function, const std::string& Message)
{
    ErrHandler(Device.c_str(), Code, Function.c_str(), Message.c_str());
}
// Three-argument convenience variants
inline void ErrHandler(const QString& Device, int Code, const QString& Message)
{
    ErrHandler(Device.toUtf8().constData(), Code, Message.toUtf8().constData());
}
inline void ErrHandler(const std::string& Device, int Code, const std::string& Message)
{
    ErrHandler(Device.c_str(), Code, Message.c_str());
}

// Minimal error display API: show a popup with title, function, and error lines
inline void sendError(const QString& title, const QString& error, const QString& function)
{
    const QString composed = QStringLiteral("%1\n%2\n%3").arg(title, function, error);
    AppLogger::instance().log(composed);
    AppLogger::instance().panel(QStringLiteral("Errors"));
}
inline void sendError(const std::string& title, const std::string& error, const std::string& function)
{
    sendError(QString::fromUtf8(title.c_str(), static_cast<int>(title.size())),
              QString::fromUtf8(error.c_str(), static_cast<int>(error.size())),
              QString::fromUtf8(function.c_str(), static_cast<int>(function.size())));
}
