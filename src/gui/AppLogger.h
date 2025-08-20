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
