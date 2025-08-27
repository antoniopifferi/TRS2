module;                              // global module fragment
#include "src/gui/AppLogger.h"
#include <QEventLoop>
#include <QTimer>

export module TestSpc;

import <vector>;
import <cmath>;
import <cstdlib>;
import <format>;

import Spc;
import Globals;
import Const;

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
        const int ms = static_cast<int>(std::max(0.0, secs) * 100.0);

        QEventLoop loop;
        QTimer::singleShot(ms, &loop, &QEventLoop::quit);
        loop.exec();
    }

    void getDataDev() override {
        // Port of GetDataTest() with light C++ cleanups
        const int numCh = P.Chann.Num;
        const int delta = numCh / 2;
        const int nBoards = P.Num.Board;
        const int nDet = P.Num.Det;

        std::vector<double> dataD(static_cast<size_t>(numCh), 0.0);

        for (int ib = 0; ib < nBoards; ++ib) {
            for (int id = 0; id < nDet; ++id) {

                // Two "lobes" as in the original code
                for (int il = 0; il < 2; ++il) {
                    // Preserve the same formulas as C version
                    const double denom = (il / 0.3 + 1 / 0.3); // NB: doubles, not integer math
                    const double weight = (1 + 2 * (id + ib * nDet));
                    const double mus = TEST_MUS / (nDet * nBoards * denom) * weight;
                    const double mua = TEST_MUA / (nDet * nBoards * denom) * weight;
                    const double r = TEST_RHO;
                    const double v = TEST_V;

                    for (int ic = 0; ic < delta; ++ic) {
                        const double t = (ic + 0.5) * P.Spc.Factor;
                        // dataD is split into two halves (il=0,1)
                        dataD[static_cast<size_t>(ic + il * delta)] =
                            (std::pow(t, -2.5) / mus) * std::exp(-mua * v * t) * std::exp(-(3.0 * r * r * mus) / (4.0 * v * t));
                    }
                }

                // Normalize area over the whole channel range
                double area = 0.0;
                for (int ic = 0; ic < numCh; ++ic) area += dataD[static_cast<size_t>(ic)];

                const double timeA = (P.Contest.Function == CONTEST_OSC ? P.Spc.TimeO : P.Spc.TimeM);

                for (int ic = 0; ic < numCh; ++ic) {
                    const double base = (area > 0.0 ? (TEST_AREA * timeA / area) * dataD[static_cast<size_t>(ic)] : 0.0);
                    const double noise = (1.0 - TEST_NOISE) + (2.0 * TEST_NOISE * std::rand()) / RAND_MAX;
                    const double value = base * noise;

                    Data[ic + id * numCh] = static_cast<T_DATA>(value);
                }
            }
        }
    }
};
