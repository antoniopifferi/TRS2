export module MicroStep;

import <iostream>;
import Step;

// Concrete device: MicroStep
export class MicroStep : public Step {
public:
    explicit MicroStep(int idx) {
        std::cout << "MicroStep constructor called" << std::endl;
        this->iS = idx;
    }
    ~MicroStep() override {
        std::cout << "MicroStep destructor called" << std::endl;
    }
    void moveStepDev(long goal) override {
        std::cout << "MicroStep moving step device to goal: " << goal << std::endl;
        // In real code, command the hardware here.
        this->actual = goal;
    }
};
