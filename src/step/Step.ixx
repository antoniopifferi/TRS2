module;                              // global module fragment (for legacy includes)
#include "src/gui/AppLogger.h"

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>

export module Step;



import Const;
import Globals;

export class Step {
public:
    // State
    long actual{};
    int  iS{};
    std::vector<long> start;
    std::vector<long> stop;
    bool diffHome{};
    bool moving{};
    long home{};
    long delta{};
    double freqActual{};
    int dir{};

    // Factory (implemented in StepFactory.ixx)
    static std::unique_ptr<Step> createStep(int iS);

    // *** Virtual, out-of-line destructor (definition below)
    virtual ~Step() = default;

    // API
    void moveStep(long* Actual, long Goal, bool Wait, bool Status);
    void setVel(double Freq);
    void initPos();
    void initStep();
    long calcGoal();

    // Device primitive
    virtual void moveStepDev(long goal) = 0;
};

// ------------------------------
// Implementations
// ------------------------------

void Step::initPos() {
    moving = false;

    // Guard step index
    if (iS < 0 || iS >= MAX_STEP) {
        start.clear(); home = actual = 0;
        return;
    }

    // If your UI stores loop as 1-based, do: int loop = P.Step[iS].Loop - 1;
    int loop = P.Step[iS].Loop;
    if (loop < 0 || loop >= MAX_LOOP) {
        start.clear(); home = actual = 0;
        return;
    }

    long num = P.Loop[loop].Num;
    if (num <= 0) {
        start.clear(); home = actual = 0;
        return;
    }

    start.resize(static_cast<size_t>(num));
    home = static_cast<long>(P.Loop[loop].Home * P.Step[iS].Factor);

    for (long il = 0; il < num; ++il) {
        const long label = P.Loop[loop].First + il * P.Loop[loop].Delta;
        start[static_cast<size_t>(il)] = static_cast<long>(P.Step[iS].Factor * label);
    }

    actual = home;
}

void Step::initStep() {
    moving = false;

    if (P.Step[iS].Mode == "CONT") {
        const double freq = std::fabs(
            P.Step[this->iS].Delta / (P.Spc.TimeM * P.Loop[P.Step[this->iS].Loop].Num)
        );
        setVel(freq);
    }
    else {
        setVel(P.Step[this->iS].Freq);
    }
}

void Step::setVel(double Freq) {
    Freq = std::fabs(Freq);
    P.Step[this->iS].FreqActual = Freq;
}

void Step::moveStep(long* Actual, long Goal, bool Wait, bool /*Status*/) {
    if (!Actual) return;
    if (*Actual == Goal) return;

    moving = true;
    const long delta = Goal - *Actual;
    dir = (delta > 0 ? 1 : -1);

    Goal = (dir > 0
        ? std::min<long>(Goal, P.Step[iS].Max)
        : std::max<long>(Goal, P.Step[iS].Min));

    moveStepDev(Goal);
    P.Spc.Trash = true;

    if (Wait) return;
    moving = false;
}

long Step::calcGoal() {
    int loop = P.Step[iS].Loop;   // if UI is 1-based: --loop;
    if (loop < 0 || loop >= MAX_LOOP) return 0;

    long idx = P.Loop[loop].Actual;
    if (idx < 0 || static_cast<size_t>(idx) >= start.size())
        return start.empty() ? 0 : start.back();

    return start[static_cast<size_t>(idx)];
}
