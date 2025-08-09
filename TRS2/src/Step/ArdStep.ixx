export module ArdStep;

import <iostream>;
import Step;

// Concrete device: ArdStep
export class ArdStep : public Step {
public:
    explicit ArdStep(int idx) {
        std::cout << "ArdStep constructor called" << std::endl;
        this->iS = idx;
    }
    ~ArdStep() override {
        std::cout << "ArdStep destructor called" << std::endl;
    }
    void moveStepDev(long goal) override {
        std::cout << "ArdStep moving step device to goal: " << goal << std::endl;
        // In real code, command the hardware here.
        this->actual = goal;
    }
};
