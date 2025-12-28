module;                              // global module fragment starts
#include "src/gui/AppLogger.h"     // <-- legacy include goes here
#include <QEventLoop>
#include <QTimer>
// (you can also put other #includes here if needed)
#include <iostream>
#include <format> // C++20 format library

export module StepTest;


import Step;
import Globals;

export class StepTest : public Step {
public:
    explicit StepTest(int idx) {
        outText("StepTest constructor called");
        this->iS = idx;
    }
    ~StepTest() override {;}

protected:
    void moveDev(long goal) override {
        this->actual = goal;

        // Delay 1s without freezing the GUI:
        //QEventLoop loop;
        //QTimer::singleShot(1000, &loop, &QEventLoop::quit);
        //loop.exec(); // processes events while waiting

        outText(std::format("Stepper {} ({}) moved to position = {}", this->iS, P.Step[this->iS].Type, this->actual));
    }
};
