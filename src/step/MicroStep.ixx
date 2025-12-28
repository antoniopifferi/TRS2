module;                   
#include <iostream>

export module MicroStep;


import Step;

// Concrete device: MicroStep
export class MicroStep : public Step {
public:
    explicit MicroStep(int idx) {
        std::cout << "MicroStep constructor called" << std::endl;
        this->iS = idx;
        //initPos();             // <-- add this
        // initStep();         // optional
    }
    ~MicroStep() override {;}

    void moveStepDev(long goal) override {
        std::cout << "MicroStep moving step device to goal: " << goal << std::endl;
        // In real code, command the hardware here.
        this->actual = goal;
    }
};
