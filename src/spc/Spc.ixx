module;                              // global module fragment (for legacy includes)
#include "src/gui/AppLogger.h"

#include <memory>
#include <vector>
#include <cmath>
#include <cstdlib>

export module Spc;


import Const;
import Globals;

// Base acquisition device (SPC)
export class Spc {
public:
    // Factory (implemented in SpcFactory.ixx)
    static std::unique_ptr<Spc> createSpc();

    virtual ~Spc() = default;

    // High-level API (device-agnostic orchestration)
    void init() { initDev(); }
    void close() { stop(false); closeDev(); }
    void pause() { pauseDev(); }

    void clear() {
        clearDev();
        //P.Spc.Zero = TimerN();
        P.Spc.Trash = false;
    }

    void start() {
        startDev();
        //P.Spc.Zero = TimerN();
        P.Spc.Started = true; // fine for TEST; specialized boards could override if needed
    }

    void restart() { restartDev(); }
    void reset(bool /*status*/, bool doClear, bool doStop) {
        if (doClear) clear();
        if (P.Spc.Trash) out(false);
        if (doStop || !P.Spc.Started) start();
        P.Spc.Trash = false;
    }

    void setTime(float seconds) {
        // Keep parity with the C path that doubles the time unless we're explicitly waiting on SPC
        if (P.Wait.Type != WAIT_SPC) seconds *= 2.0f;
        setTimeDev(seconds);
    }

    void stop(bool /*status*/) {
        stopDev();
        calcTime();
        P.Spc.Started = false;
    }

    void wait() { waitDev(); }
    void get() { getDataDev(); }

    void out(bool /*status*/) {
        if (P.Spc.Started) calcTime();
        get();
        dataCopy();
        // By-architecture reversals/subtractions for VARRO/SILENA are intentionally
        // not applied for TEST; add here if you later port those devices.
    }

protected:
    // Device primitives to be implemented by subclasses
    virtual void initDev() = 0;
    virtual void closeDev() = 0;
    virtual void pauseDev() = 0;
    virtual void clearDev() = 0;
    virtual void startDev() = 0;
    virtual void restartDev() = 0;
    virtual void setTimeDev(float seconds) = 0;
    virtual void stopDev() = 0;
    virtual void waitDev() = 0;
    virtual void getDataDev() = 0;

    // Helpers ported from the C version (generic where possible)
    void calcTime() {
        // Generic (TEST/DEMO/others that don't expose board-specific elapsed time):
        //double now = TimerN();
        //P.Spc.EffTime[0] = now - P.Spc.Zero;
        //P.Spc.Zero = now;
    }

    void dataCopy() {
    //    const int is_meas = (P.Contest.Function == CONTEST_MEAS);

    //    if (!is_meas) {
    //        for (int ib = 0; ib < P.Num.Board; ++ib)
    //            for (int id = 0; id < P.Num.Det; ++id)
    //                for (int ic = 0; ic < P.Chann.Num; ++ic)
    //                    D.Osc[id + ib * P.Num.Det][ic] = D.Buffer[ib][ic + id * P.Chann.Num];
    //    }
    //    else {
    //        for (int ib = 0; ib < P.Num.Board; ++ib) {
    //            for (int id = 0; id < P.Num.Det; ++id) {
    //                long page = P.Filter.Page[P.Acq.Actual][ib][id];
    //                if (page != -1) {
    //                    P.Page[page].Acq = P.Acq.Actual;
    //                    P.Page[page].TimeNom = P.Spc.TimeM;
    //                    P.Page[page].TimeEff = P.Spc.EffTime[ib];
    //                    for (int ic = 0; ic < P.Chann.Num; ++ic)
    //                        D.Data[P.Frame.Actual][page][ic] += D.Buffer[ib][ic + id * P.Chann.Num];
    //                    if (P.Info.SubHeader) CompileSub(P.Ram.Actual, P.Frame.Actual, page);
    //                }
    //            }
    //        }
    //    }
    }
};

export std::unique_ptr<Spc> spc[1];
