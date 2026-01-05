module;

#include <Windows.h>

extern "C" {
#include "lib/PI_GCS2_DLL.h"          // PI Software Suite (GCS2 DLL)
}
#include "src/gui/AppLogger.h"

#include <iostream>
#include <format>
#include <cstdio>
#include <cstring>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>

export module StepPi;

import Step;
import Globals;

// PI SPECIFIC CONSTANTS (GCS / C-663) – strings for GCS
static constexpr const char* PI_CMD_HOME = "FRF";
static constexpr const char* PI_CMD_VEL  = "VEL";
static constexpr const char* PI_CMD_MOV  = "MOV";
static constexpr const char* PI_CMD_POSQ = "POS?";
static constexpr const char* PI_CMD_ONTQ = "ONT?";
static constexpr const char* PI_CMD_STP  = "STP";

static constexpr int         PI_BAUDRATE = 115200;
static constexpr const char* PI_AXIS = "1";
static constexpr long        PI_DISCONNECTED_POS = 2147483643;

inline void errDev(int code, const char* what)
{
    ErrHandler("PI", code, what ? what : "");
}

// ---- PI-GCS helpers ----
namespace
{
    inline int lastPiError(int id) { return PI_GetError(id); }

    inline bool piCmd(int id, const std::string& cmd, const char* what)
    {
        if (!PI_GcsCommandset(id, cmd.c_str())) { errDev(lastPiError(id), what); return false; }
        return true;
    }

    inline bool piQuery(int id, const std::string& cmd, std::string& out, const char* what)
    {
        out.clear();
        if (!PI_GcsCommandset(id, cmd.c_str())) { errDev(lastPiError(id), what); return false; }
        char buf[4096]{};
        if (!PI_GcsGetAnswer(id, buf, static_cast<int>(sizeof(buf)))) { errDev(lastPiError(id), what); return false; }
        out.assign(buf);
        return true;
    }

    inline bool piQueryInt(int id, const std::string& cmd, int& v, const char* what)
    {
        std::string s; if (!piQuery(id, cmd, s, what)) return false; v = std::strtol(s.c_str(), nullptr, 0); return true;
    }
    inline bool piQueryDouble(int id, const std::string& cmd, double& v, const char* what)
    {
        std::string s; if (!piQuery(id, cmd, s, what)) return false; v = std::strtod(s.c_str(), nullptr); return true;
    }
}

export class StepPi : public Step {
public:
    explicit StepPi(int idx) { this->iS = idx; }
    ~StepPi() override = default;

protected:
    void moveDev(long goal) override
    {
        if (goal == P.Step[iS].Actual) return;
        if (id_ < 0) { errDev(-1, "PI not connected"); return; }
        const double pos = static_cast<double>(goal);
        const std::string cmd = std::string(PI_CMD_MOV) + " " + PI_AXIS + " " + std::to_string(pos);
        if (!piCmd(id_, cmd, "PI MOV")) return;
        actual = goal;
    }

    void initDev() override
    {
        const int com = P.Step[iS].Com;
        id_ = PI_ConnectRS232(com, PI_BAUDRATE);
        if (id_ < 0) { errDev(id_, "PI_ConnectRS232"); id_ = -1; return; }
        std::string idn; if (!piQuery(id_, "IDN?", idn, "PI IDN?")) { PI_CloseConnection(id_); id_ = -1; return; }
        setVelDev(P.Step[iS].Freq);
    }

    void closeDev() override
    {
        if (id_ >= 0) { PI_CloseConnection(id_); id_ = -1; }
    }

    void setVelDev(double Freq) override
    {
        if (id_ < 0) { errDev(-1, "PI not connected"); return; }
        const std::string cmd = std::string(PI_CMD_VEL) + " " + PI_AXIS + " " + std::to_string(Freq);
        (void)piCmd(id_, cmd, "PI VEL");
    }

    void waitDev(long /*Goal*/) override
    {
        if (id_ < 0) { errDev(-1, "PI not connected"); return; }
        constexpr auto poll = std::chrono::milliseconds(2);
        constexpr auto timeout = std::chrono::seconds(120);
        const auto t0 = std::chrono::steady_clock::now();
        for (;;) {
            int ont = 0;
            if (!piQueryInt(id_, std::string(PI_CMD_ONTQ) + " " + PI_AXIS, ont, "PI ONT?")) return;
            if (ont != 0) break;
            if (std::chrono::steady_clock::now() - t0 > timeout) { errDev(-2, "PI waitDev timeout"); break; }
            std::this_thread::sleep_for(poll);
        }
    }

    void tellPosDev(long* Actual) override
    {
        if (!Actual) return;
        if (id_ < 0) { *Actual = PI_DISCONNECTED_POS; return; }
        double pos = 0.0; if (!piQueryDouble(id_, std::string(PI_CMD_POSQ) + " " + PI_AXIS, pos, "PI POS?")) return;
        *Actual = static_cast<long>(pos);
    }

    void stopDev() override
    {
        if (id_ < 0) { errDev(-1, "PI not connected"); return; }
        (void)piCmd(id_, PI_CMD_STP, "PI STP");
    }

    void defineHomeDev() override { /* Optional FRF */ }

private:
    int id_ = -1; // PI DLL connection ID
};