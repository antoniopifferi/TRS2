#pragma once
#include <QObject>
#include <QString>


class AppLogger : public QObject {
    Q_OBJECT
public:
    static AppLogger& instance() { static AppLogger inst; return inst; }

    // Call this from anywhere in your code (any thread)
    void log(const QString& msg) { emit message(msg); }

signals:
    void message(const QString& msg);

private:
    AppLogger() = default;
    Q_DISABLE_COPY(AppLogger)
};

inline void outText(const QString& msg) {
    AppLogger::instance().log(msg);
}


#pragma once
