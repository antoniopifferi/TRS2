module;                              // global module fragment starts
#include "src/gui/AppLogger.h"     // <-- legacy include goes here
// (you can also put other #includes here if needed)

#include <iostream>

export module ArdStep;


import Step;

// Concrete device: ArdStep
export class ArdStep : public Step {
public:
    explicit ArdStep(int idx) {
        outText("ArdStep constructor called"); // <-- restore this line
        this->iS = idx;
        //initPos();             // <-- add this
        // initStep();         // optional, if you want velocity set here
    }
    ~ArdStep() override {
        outText("ArdStep destructor called");
    }
    void moveStepDev(long goal) override {
        std::cout << "ArdStep moving step device to goal: " << goal << std::endl;
        // In real code, command the hardware here.
        this->actual = goal;
    }
};
