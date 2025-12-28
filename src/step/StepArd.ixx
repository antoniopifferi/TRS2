module;
#include "src/gui/AppLogger.h"
#include <QSerialPort>
#include <QString>
#include <iostream>
#include <format>

export module StepArd;

import Step;
import Globals;

// ARDUINO SPECIFIC CONSTANTS
static constexpr char ARD_LCD      = 'W';
static constexpr char ARD_HOLD     = 'H';
static constexpr char ARD_FMIN     = 'M';
static constexpr char ARD_FDELTA   = 'A';
static constexpr char ARD_HOME     = 'I';
static constexpr char ARD_VEL      = 'V';
static constexpr char ARD_GOTO     = 'G';
static constexpr char ARD_TELL     = 'T';
static constexpr char ARD_STOP     = 'F';
static constexpr char ARD_END      = 'E';
static constexpr char ARD_TERM     = ';';
static constexpr int  ARD_GETLENGTH= 16;
static constexpr int  ARD_HOLD_OFF = 0;
static constexpr int  ARD_HOLD_MEAS= 1;
static constexpr int  ARD_HOLD_ON  = 2;
static constexpr int  ARD_LCD_OFF  = 0;
static constexpr int  ARD_LCD_ALL  = 1;
static constexpr int  ARD_LCD_END  = 2;
static constexpr int  ARD_BAUDRATE = 115200;
static constexpr int  ARD_PARITY   = 0;
static constexpr int  ARD_DATABITS = 8;
static constexpr int  ARD_STOPBITS = 1;
// Request parameter for TELL (kept from legacy):
static constexpr long ARD_TELL_PARAM = 100;
// IO timeouts (ms)
static constexpr int  ARD_WRITE_TIMEOUT_MS = 300;
static constexpr int  ARD_READ_TOTAL_MS    = 800;
static constexpr int  ARD_READ_SLICE_MS    = 100;

export class StepArd : public Step {
public:
    explicit StepArd(int idx) { this->iS = idx; }
    ~StepArd() override = default;

protected:
    void moveStepDev(long goal) override {
        long v = (goal < 0) ? goal - 1 : goal;
        sendDev(ARD_GOTO, v);
        actual = goal;
    }

    void initDev() override {
        axis_ = P.Step[iS].Axis + 1;
        const int com = P.Step[iS].Com;
        portName_ = QStringLiteral("COM%1").arg(com);
        port_.setPortName(portName_);
        port_.setBaudRate(ARD_BAUDRATE);
        port_.setDataBits(QSerialPort::Data8);
        port_.setParity(QSerialPort::NoParity);
        port_.setStopBits(QSerialPort::OneStop);
        port_.setFlowControl(QSerialPort::NoFlowControl);
        ensureOpen();
    }

    void closeDev() override {
        sendDev(ARD_GOTO, 0); // idle
        if (port_.isOpen()) port_.close();
    }

    void setVelDev(double Freq) override { sendDev(ARD_VEL, static_cast<long>(Freq)); }
    void waitDev(long) override { /* no-op */ }

    void tellPosDev(long* Actual) override {
        if (!Actual) return;
        if (auto ans = talkDev(ARD_TELL, ARD_TELL_PARAM)) *Actual = *ans;
    }

    void stopDev() override { sendDev(ARD_STOP, 0); }
    void defineHomeDev() override { sendDev(ARD_HOME, 0); }

private:
    QSerialPort port_{};
    QString portName_{};
    int axis_ = 1;

    void ensureOpen() {
        if (!port_.isOpen()) {
            if (!port_.open(QIODevice::ReadWrite)) {
                std::cerr << "Serial open failed for " << portName_.toStdString() << ": "
                          << port_.errorString().toStdString() << '\n';
            }
        }
    }

    // minimal write-only
    void sendDev(char cmd, long value) {
        ensureOpen();
        const std::string s = std::format("{}{}{}\n", axis_, cmd, value);
        const QByteArray out(s.data(), static_cast<int>(s.size()));
        if (port_.write(out) != out.size() || !port_.waitForBytesWritten(ARD_WRITE_TIMEOUT_MS)) {
            std::cerr << "Write/flush failed on " << portName_.toStdString() << '\n';
        }
    }

    // minimal send+read
    std::optional<long> talkDev(char cmd, long value) {
        sendDev(cmd, value);
        QByteArray in;
        for (int waited = 0; waited < ARD_READ_TOTAL_MS; waited += ARD_READ_SLICE_MS) {
            if (port_.waitForReadyRead(ARD_READ_SLICE_MS)) { in += port_.readAll(); if (in.contains('\n')) break; }
        }
        if (in.isEmpty()) return std::nullopt;
        std::string resp(in.constData(), static_cast<size_t>(in.size()));
        std::string num;
        for (char c : resp) { if (c == '-' || (c >= '0' && c <= '9')) num.push_back(c); else if (!num.empty()) break; }
        if (num.empty()) return std::nullopt;
        try { return std::stol(num); } catch (...) { return std::nullopt; }
    }
};
