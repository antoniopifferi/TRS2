#include <iostream>
#include <memory>
#include <vector>

#include "src/run/runKernel.h"
#include "src/gui/AppLogger.h"
#include "src/gui/trs2.h"

import Const;
import Globals;
import Step;
import StepFactory;
import ArdStep;
import MicroStep;
import Spc;
import TestSpc;
import SpcFactory;
import Data;

void loopGet(int loop) {
    int l = loop;
    for (int iL = 0; iL < MAX_LOOP; iL++) {
        if (P.Loop[iL].Num > 0) {
            P.Loop[iL].Actual = l % P.Loop[iL].Num;
            l /= P.Loop[iL].Num;
        } else {
            P.Loop[iL].Actual = 0;
        }
    }
}

void runKernel() {

    // GUI
    P.Num.Board = 1;
	P.Num.Det = 1;
    P.Contest.Function = CONTEST_OSC;

    // define variables
    std::unique_ptr<Step> steps[MAX_STEP];
    std::unique_ptr<Spc> spc[1];

    // allocate data buffer once based on bins count
    D.data.resize(static_cast<std::size_t>(P.Bins.Num));

    // update all GUI
    GUI->readAll();

    // display Output
    GUI->displayPanel("Output");

    // InitLoop
    for(int iL=0;iL<5;iL++) P.Loop[iL].Num=(P.Loop[iL].Last-P.Loop[iL].First)/P.Loop[iL].Delta+1;

	 //InitSteps
    for (int iS = 0; iS < MAX_STEP; ++iS) {
        steps[iS] = createStep(iS);
        if(steps[iS]) steps[iS]->initStep();
        if(steps[iS]) steps[iS]->initPos();
        }

	// InitSpc
    spc[0] = createSpc();
    if (spc[0]) spc[0]->init();

	int loop = 0;
    while (!P.Command.Abort && loop<P.Loop[0].Num*P.Loop[1].Num * P.Loop[2].Num * P.Loop[3].Num * P.Loop[4].Num) {
		
        loopGet(loop);

        bool status=false;

        for (auto& s : steps) {
            if (s) s->moveStep(&s->actual, s->calcGoal(), P.Step[s->iS].Mode != "MULTI", status);
        }
        if (spc[0]) {
            spc[0]->wait();
            spc[0]->get();
        }
        
        outText(std::format("Loop = {}", P.Loop[4].Actual));
        
        std::vector<double> t(static_cast<size_t>(P.Bins.Num));
        for (int ib = 0; ib < P.Bins.Num; ++ib)
            t[static_cast<size_t>(ib)] = (static_cast<double>(ib) + 0.5) * P.Spc.Factor;
        
        // Plot all points at once (convert D.data to long)
        std::vector<long> y; y.reserve(D.data.size());
        for (std::uint32_t v : D.data) y.push_back(static_cast<long>(v));
        GUI->displayPlot(t, y);

		loop++;
    }

    displayPanel("Parm");
}
