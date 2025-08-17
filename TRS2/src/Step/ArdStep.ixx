module;                              // global module fragment starts
#include "GuiSource/AppLogger.h"     // <-- legacy include goes here
// (you can also put other #includes here if needed)

export module ArdStep;

import <iostream>;
import Step;

// Concrete device: ArdStep
export class ArdStep : public Step {
public:
    explicit ArdStep(int idx) {
        //std::cout << "ArdStep constructor called" << std::endl;
        //outText("ArdStep constructor called");
        this->iS = idx;
    }
    ~ArdStep() override {
        //outText("ArdStep destructor called");
    }
    void moveStepDev(long goal) override {
        std::cout << "ArdStep moving step device to goal: " << goal << std::endl;
        // In real code, command the hardware here.
        this->actual = goal;
    }
};
