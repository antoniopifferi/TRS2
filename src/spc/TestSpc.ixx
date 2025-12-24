module;                              // global module fragment
#include "src/gui/AppLogger.h"
#include <QEventLoop>
#include <QTimer>
#include <format>

export module TestSpc;


import Spc;
import Globals;
import Data;

// Concrete device: TestSpc (software generator mirroring TestSpc.c)
export class TestSpc : public Spc {
public:
    TestSpc() { outText("TestSpc constructor"); }
    ~TestSpc() override { outText("TestSpc destructor"); }

protected:
    // Device primitive impls ---------------------------------------------------
    void initDev() override { /* nothing to init for pure SW generator */ }
    void closeDev() override { /* nothing */ }
    void pauseDev() override { /* nothing */ }
    void clearDev() override { /* base clear() handled generic bookkeeping */ }
    void startDev() override { /* nothing */ }
    void restartDev() override { /* identical to start for TEST */ }
    void stopDev() override { /* nothing */ }

    void setTimeDev(float seconds) override {
        // For TEST we store into TimeM so downstream logic (e.g., UI, copy) can read it
        P.Spc.TimeM = seconds;
    }

    void waitDev() override {
        // C path: Delay((P.Contest.Function==CONTEST_OSC ? P.Spc.TimeO : P.Spc.TimeM));
        const double secs = (P.Contest.Function == CONTEST_OSC ? P.Spc.TimeO : P.Spc.TimeM);
        const int ms = static_cast<int>(std::max(0.0, secs) * 1000.0);

        QEventLoop loop;
        QTimer::singleShot(ms, &loop, &QEventLoop::quit);
        loop.exec();
    }

    void getDataDev() override {
        const int numCh = P.Chann.Num;
        const int numDet = P.Num.Det;
        D.data.resize(static_cast<std::size_t>(numCh * numDet));
        for (int id = 0; id < numDet; ++id) {
            for (int ic = 0; ic < numCh; ++ic) {
                const long value = static_cast<long>((ic + 1) * (id + 1));
                D.data[static_cast<std::size_t>(ic + id * numCh)] = static_cast<std::uint16_t>(value);
            }
        }
        outText(std::format("TestSpc filled {} values", D.data.size()));
    }
};
