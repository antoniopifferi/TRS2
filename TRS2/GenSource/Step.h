#ifndef STEP_H
#define STEP_H

#include <string>
#include <vector>
#include <chrono>
#include <iostream>

class Step {
public:
    // Variables
    long actual;
    int iS;
    std::vector<long> start;
    std::vector<long> stop;
    bool diffHome;
    bool moving;
    long home;
    long delta;

    // Functions
    static Step* createStep(int iS);

    virtual ~Step() {
        std::cout << "Step destructor called" << std::endl;
    };

    void moveStep(long *Actual, long Goal, int Step, bool Wait, bool Status);

    virtual void moveStepDev(long goal) = 0;

    void setVel(int Step, double Freq);

    void initPos(void);

    void initStep(int Step);

    long calcGoal(char Step);
};

#endif // STEP_H
