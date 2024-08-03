#ifndef MICROSTEP_H
#define MICROSTEP_H

#include "GenSource/Step.h"

class MicroStep : public Step {
public:
    // Constructor
    MicroStep(int iS);

    // Destructor
    ~MicroStep() override;

    // Implementation of the pure virtual function
    void moveStepDev(long goal) override;
};

#endif // MICROSTEP_H
