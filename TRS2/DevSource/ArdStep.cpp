#include "DevSource/ArdStep.h"
#include <iostream>

// Constructor
ArdStep::ArdStep(int iS) {
    std::cout << "ArdStep constructor called" << std::endl;
}

// Destructor
ArdStep::~ArdStep() {
    std::cout << "ArdStep destructor called" << std::endl;
}

// Implementation of the pure virtual function
void ArdStep::moveStepDev(long goal) {
    std::cout << "ArdStep moving step device to goal: " << goal << std::endl;
}
