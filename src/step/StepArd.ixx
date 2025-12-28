module;                              // global module fragment starts
#include "src/gui/AppLogger.h"    
#include <QEventLoop>
#include <QTimer>
#include <iostream>
#include <format> // C++20 format library

export module StepArd;


import Step;
import Globals;

// Concrete device: TestStep
export class StepArd : public Step {
public:
    explicit StepArd(int idx) {
        outText("TestStep constructor called");
        this->iS = idx;
    }
    ~StepArd() override { ; }

     void moveStepDev(long goal) override {
        this->actual = goal;
    }
};
