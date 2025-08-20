module;                              // global module fragment
#include "src/gui/AppLogger.h"

export module SpcFactory;

import <memory>;
import <string>;

import Spc;
import Globals;

// Concrete devices
import TestSpc;

// Note: We mirror the StepFactory pattern and dispatch by string type (e.g. "TEST")
export std::unique_ptr<Spc> Spc::createSpc() {
    const std::string& type = P.Spc.Type;  // keep parity with StepFactory string selection
    outText("Enter SpcFactory");

    if (type == "TEST") {
        return std::make_unique<TestSpc>();
    }

    // Add other concrete Spc subclasses here as you port them:
    // else if (type == "SPC300") return std::make_unique<Spc300>();
    // ...

    return nullptr;
}
