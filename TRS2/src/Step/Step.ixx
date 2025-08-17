export module Step;

import <string>;
import <vector>;
import <memory>;
import <fstream>;
import <sstream>;
import <iostream>;
import <cmath>;
import <algorithm>;

import Const;
import Globals;

export class Step {
public:
    // Variables (from original Step.h)
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

    // Factory (defined in StepFactory.ixx to avoid module cycles)
    static std::unique_ptr<Step> createStep(int iS);

    virtual ~Step() = default;

    // High-level ops
    void moveStep(long* Actual, long Goal, bool Wait, bool Status);
    void setVel(double Freq);
    void initPos(void);
    void initStep();
    long calcGoal();

    // Device-specific primitive
    virtual void moveStepDev(long goal) = 0;
};

// ------------------------------
// Implementations
// ------------------------------

void Step::initPos(void) {
    moving = false;

    // 1) Guard the step index
    if (iS < 0 || iS >= MAX_STEP) {
        // optional: log
        return;
    }

    // 2) Get loop index and guard it
    int loop = P.Step[iS].Loop;                           // if UI is 1-based, this may be 1..MAX
    if (loop < 0 || loop >= MAX_LOOP) {
        // optional: log
        start.clear();
        home = actual = 0;
        return;
    }

    // 3) Number of points and guard it
    long num = P.Loop[loop].Num;
    if (num <= 0) {
        start.clear();
        home = actual = 0;
        return;
    }

    // 4) Build default positions (file-reading path still commented; ok)
    start.resize(static_cast<size_t>(num));
    home = static_cast<long>(P.Loop[loop].Home * P.Step[iS].Factor);

    for (long il = 0; il < num; ++il) {
        const long label = P.Loop[loop].First + il * P.Loop[loop].Delta;
        start[static_cast<size_t>(il)] =
            static_cast<long>(P.Step[iS].Factor * label);
    }

    actual = home; // start from home
}
void Step::initStep(){
    moving=false;

    if(P.Step[iS].Mode=="CONT") {
        const double freq = std::fabs(P.Step[this->iS].Delta/(P.Spc.TimeM*P.Loop[P.Step[this->iS].Loop].Num));
        setVel(freq);
    } else {
        setVel(P.Step[this->iS].Freq);
    }
}

void Step::setVel(double Freq){
    Freq = std::fabs(Freq);
    P.Step[this->iS].FreqActual = Freq;
}

#include <algorithm> // Ensure this is included for std::min and std::max

void Step::moveStep(long *Actual, long Goal, bool Wait, bool /*Status*/) {
    if (*Actual == Goal) return;
    moving = true;
    const long delta = Goal - *Actual;
    dir = (delta > 0 ? 1 : -1);

    Goal = (dir > 0 ? std::min<long>(Goal, P.Step[iS].Max) : std::max<long>(Goal, P.Step[iS].Min));

    moveStepDev(Goal);

    P.Spc.Trash = true;

    if (Wait) return;

    moving = false;
}

long Step::calcGoal() {
    int loop = P.Step[iS].Loop;
    // If loop is 1-based in UI, use: loop -= 1;

    if (loop < 0 || loop >= MAX_LOOP) return 0;

    long index = P.Loop[loop].Actual;
    if (index < 0 || static_cast<size_t>(index) >= start.size())
        return start.empty() ? 0 : start.back();

    return start[static_cast<size_t>(index)];
}
