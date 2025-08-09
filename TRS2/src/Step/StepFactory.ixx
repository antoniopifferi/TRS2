export module StepFactory;

import <memory>;
import <string>;

import Step;
import Globals;

import MicroStep;
import ArdStep;

// Definition of Step::createStep placed in a separate module to avoid cycles
export std::unique_ptr<Step> Step::createStep(int iS) {
    const std::string& type = P.Step[iS].Type;
    if (type == "MICRO") {
        return std::unique_ptr<Step>(new MicroStep(iS));
    } else if (type == "ARD") {
        return std::unique_ptr<Step>(new ArdStep(iS));
    }
    return nullptr;
}
