module;                              // global module fragment starts
#include "src/gui/AppLogger.h"     // <-- legacy include goes here
// (you can also put other #includes here if needed)
#include <memory>
#include <string>


export module StepFactory;



import Step;
import Globals;

import MicroStep;
import ArdStep;
import TestStep;

export std::unique_ptr<Step> createStep(int iS)
{
    const std::string& type = P.Step[iS].Type;
    outText("Enter the Factory constructor called");

    if (type == "MICRO") {
        return std::make_unique<MicroStep>(iS); // Use std::make_unique for better clarity and safety
    }
    else if (type == "ARD") {
        return std::make_unique<ArdStep>(iS); // Use std::make_unique for better clarity and safety
    }
    else if (type == "TEST") {
        return std::make_unique<TestStep>(iS); // Use std::make_unique for better clarity and safety
    }
    return nullptr;
}
