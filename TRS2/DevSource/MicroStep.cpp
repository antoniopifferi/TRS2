#include "DevSource/MicroStep.h"
#include <iostream>

// Constructor
MicroStep::MicroStep(int iS) {
    std::cout << "MicroStep constructor called" << std::endl;
}

// Destructor
MicroStep::~MicroStep() {
    std::cout << "MicroStep destructor called" << std::endl;
}

// Implementation of the pure virtual function
void MicroStep::moveStepDev(long goal) {
    std::cout << "MicroStep moving step device to goal: " << goal << std::endl;
}
