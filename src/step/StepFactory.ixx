module;                              // global module fragment starts
#include "src/gui/AppLogger.h"     // <-- legacy include goes here
// (you can also put other #includes here if needed)
#include <memory>
#include <string>


export module StepFactory;



import Step;
import Globals;

import StepMicro;
import StepArd;
import StepTest;
import StepPi;

export std::unique_ptr<Step> createStep(int iS)
{
    const std::string& type = P.Step[iS].Type;
    outText("Enter the Factory constructor called");

    if (type == "MICRO") {
        return std::make_unique<StepMicro>(iS); // Use std::make_unique for better clarity and safety
    }
    else if (type == "ARD") {
        return std::make_unique<StepArd>(iS); // Use std::make_unique for better clarity and safety
    }
    else if (type == "TEST") {
        return std::make_unique<StepTest>(iS); // Use std::make_unique for better clarity and safety
    }
    else if (type == "PI") {
        return std::make_unique<StepPi>(iS); // Use std::make_unique for better clarity and safety
    }
    return nullptr;
}
