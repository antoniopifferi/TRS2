export module Step; // Declare this as a module interface

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <memory>
#include "GenSource/Parm.h"
#include "DevSource/ArdStep.h"

// Exported interface
export class Step {
public:
    long actual;
    int iS;
    std::vector<long> start;
    std::vector<long> stop;
    bool diffHome;
    bool moving;
    long home;
    long delta;
    double freqActual;
    int dir;

    std::string Type;
    int Com;
    int Axis;
    std::string Mode;
    std::string Sign;
    int Loop;
    bool Hold;
    bool Lcd;
    std::string FName;
    long Min;
    long Max;
    long FreqMin;
    long FreqMax;
    long FreqDelta;
    long Freq;
    double Factor;
    bool Sort;

    static std::unique_ptr<Step> createStep(int iS);

    virtual ~Step() {
        std::cout << "Step destructor called" << std::endl;
    };

    void moveStep(long* Actual, long Goal, bool Wait, bool Status);
    virtual void moveStepDev(long goal) = 0;
    void setVel(int Step, double Freq);
    void initPos(void);
    void initStep(int Step);
    long calcGoal(int Step);
};

// Implementation
std::unique_ptr<Step> Step::createStep(int iS) {
    // Implementation of createStep
    std::unique_ptr<Step> step = nullptr;
    // ... Your code here ...
    return step;
}

void Step::initPos() {
    // Implementation of initPos
    // ... Your code here ...
}

// Additional method implementations...
