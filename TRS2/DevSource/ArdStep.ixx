export module ArdStep;

import GenSource.Step; // Importing the required module or library for 'Step'.

#include <iostream> // For standard I/O operations.

export class ArdStep : public Step {
public:
    // Constructor
    ArdStep(int iS) {
        std::cout << "ArdStep constructor called" << std::endl;
    }

    // Destructor
    ~ArdStep() override {
        std::cout << "ArdStep destructor called" << std::endl;
    }

    // Implementation of the pure virtual function
    void moveStepDev(long goal) override {
        std::cout << "ArdStep moving step device to goal: " << goal << std::endl;
    }
};
