#ifndef ARDSTEP_H
#define ARDSTEP_H

#include "GenSource/Step.h"

class ArdStep : public Step {
public:
    // Constructor
    ArdStep(int iS);

    // Destructor
    ~ArdStep() override;

    // Implementation of the pure virtual function
    void moveStepDev(long goal) override;
};

#endif // ARDSTEP_H
