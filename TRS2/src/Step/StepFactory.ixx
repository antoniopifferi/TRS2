module;                              // global module fragment starts
#include "GuiSource/AppLogger.h"     // <-- legacy include goes here
// (you can also put other #includes here if needed)

export module StepFactory;

import <memory>;
import <string>;

import Step;
import Globals;

import MicroStep;
import ArdStep;
import MicroStep;

// Ensure the correct namespace is used for unique_ptr
export std::unique_ptr<Step> Step::createStep(int iS)
{
    const std::string& type = P.Step[iS].Type;
    outText("Enter the Factory constructor called");

    if (type == "MICRO") {
        return std::make_unique<MicroStep>(iS); // Use std::make_unique for better clarity and safety
    }
    else if (type == "ARD") {
        return std::make_unique<ArdStep>(iS); // Use std::make_unique for better clarity and safety
    }
    return nullptr;
}
