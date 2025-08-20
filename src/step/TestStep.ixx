module;                              // global module fragment starts
#include "src/gui/AppLogger.h"     // <-- legacy include goes here
#include <QEventLoop>
#include <QTimer>
// (you can also put other #includes here if needed)

export module TestStep;

import <iostream>;
import <format>; // C++20 format library
import Step;
import Globals;

// Concrete device: TestStep
export class TestStep : public Step {
public:
    explicit TestStep(int idx) {
        outText("TestStep constructor called");
        this->iS = idx;
    }
    ~TestStep() override {
        outText("TestStep destructor called");
    }
    void moveStepDev(long goal) override {
        this->actual = goal;

        // Delay 1s without freezing the GUI:
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, &QEventLoop::quit);
        loop.exec(); // processes events while waiting

        outText(std::format("Stepper {} ({}) moved to position = {}", this->iS, P.Step[this->iS].Type, this->actual));
    }
};
