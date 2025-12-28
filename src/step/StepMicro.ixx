module;
#include "src/gui/AppLogger.h"
#include <QSerialPort>
#include <QString>
#include <iostream>
#include <format>

export module StepMicro;

import Step;
import Globals;

// MICRO SPECIFIC CONSTANTS
static constexpr char MICRO_LCD      = 'W';
static constexpr char MICRO_HOLD     = 'H';
static constexpr char MICRO_FMIN     = 'M';
static constexpr char MICRO_FDELTA   = 'A';
static constexpr char MICRO_HOME     = 'I';
static constexpr char MICRO_VEL      = 'V';
static constexpr char MICRO_GOTO     = 'G';
static constexpr char MICRO_TELL     = 'T';
static constexpr char MICRO_STOP     = 'F';
static constexpr char MICRO_END      = 'E';
static constexpr char MICRO_TERM     = ';';
static constexpr int  MICRO_GETLENGTH= 16;
static constexpr int  MICRO_HOLD_OFF = 0;
static constexpr int  MICRO_HOLD_MEAS= 1;
static constexpr int  MICRO_HOLD_ON  = 2;
static constexpr int  MICRO_LCD_OFF  = 0;
static constexpr int  MICRO_LCD_ALL  = 1;
static constexpr int  MICRO_LCD_END  = 2;
static constexpr int  MICRO_BAUDRATE = 2000000; // MICRO2 default
static constexpr int  MICRO_PARITY   = 0;
static constexpr int  MICRO_DATABITS = 8;
static constexpr int  MICRO_STOPBITS = 1;
static constexpr long MICRO_TELL_PARAM = 0;
static constexpr int  MICRO_WRITE_TIMEOUT_MS = 300;
static constexpr int  MICRO_READ_TOTAL_MS    = 800;
static constexpr int  MICRO_READ_SLICE_MS    = 100;

export class StepMicro : public Step {
public:
    explicit StepMicro(int idx) { this->iS = idx; }
    ~StepMicro() override = default;

protected:
    void moveDev(long goal) override {
        long v = (goal < 0) ? goal - 1 : goal;
        sendDev(MICRO_GOTO, v);
        actual = goal;
    }

    void initDev() override {
        axis_ = P.Step[iS].Axis + 1;
        const int com = P.Step[iS].Com;
        portName_ = QStringLiteral("COM%1").arg(com);
        port_.setPortName(portName_);
        port_.setBaudRate(MICRO_BAUDRATE);
        port_.setDataBits(QSerialPort::Data8);
        port_.setParity(QSerialPort::NoParity);
        port_.setStopBits(QSerialPort::OneStop);
        port_.setFlowControl(QSerialPort::NoFlowControl);
        ensureOpen();

        // Initial configuration
        sendDev(MICRO_LCD, static_cast<long>(P.Step[iS].Lcd));
        sendDev(MICRO_HOLD, static_cast<long>(P.Step[iS].Hold));
        sendDev(MICRO_FMIN, static_cast<long>(P.Step[iS].FreqMin));
        sendDev(MICRO_VEL,  static_cast<long>(P.Step[iS].Freq));
        sendDev(MICRO_FDELTA, static_cast<long>(P.Step[iS].FreqDelta));
    }

    void closeDev() override {
        sendDev(MICRO_END, 0);
        if (port_.isOpen()) port_.close();
    }

    void setVelDev(double Freq) override { sendDev(MICRO_VEL, static_cast<long>(Freq)); }
    void waitDev(long) override { /* no-op */ }

    void tellPosDev(long* Actual) override {
        if (!Actual) return;
        if (auto ans = talkDev(MICRO_TELL, MICRO_TELL_PARAM)) *Actual = *ans;
    }

    void stopDev() override { sendDev(MICRO_STOP, 0); }
    void defineHomeDev() override { sendDev(MICRO_HOME, 0); }

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

    // write-only
    void sendDev(char cmd, long value) {
        ensureOpen();
        const std::string s = std::format("{}{}{}\n", axis_, cmd, value);
        const QByteArray out(s.data(), static_cast<int>(s.size()));
        if (port_.write(out) != out.size() || !port_.waitForBytesWritten(MICRO_WRITE_TIMEOUT_MS)) {
            std::cerr << "Write/flush failed on " << portName_.toStdString() << '\n';
        }
    }

    // send + read
    std::optional<long> talkDev(char cmd, long value) {
        sendDev(cmd, value);
        return getDev();
    }

    // read-only
    std::optional<long> getDev() {
        ensureOpen();
        QByteArray in;
        for (int waited = 0; waited < MICRO_READ_TOTAL_MS; waited += MICRO_READ_SLICE_MS) {
            if (port_.waitForReadyRead(MICRO_READ_SLICE_MS)) {
                in += port_.readAll();
                if (in.contains('\n')) break;
            }
        }
        if (in.isEmpty()) return std::nullopt;
        std::string resp(in.constData(), static_cast<size_t>(in.size()));
        std::string num;
        for (char c : resp) {
            if (c == '-' || (c >= '0' && c <= '9')) num.push_back(c);
            else if (!num.empty()) break;
        }
        if (num.empty()) return std::nullopt;
        try { return std::stol(num); } catch (...) { return std::nullopt; }
    }
};


