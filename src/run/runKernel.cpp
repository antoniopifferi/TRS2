#include <iostream>
#include <memory>
#include <vector>

#include "src/run/runKernel.h"
#include "src/gui/AppLogger.h"
#include "src/gui/trs2.h"

import Const;
import Globals;
import Step;
import ArdStep;
import MicroStep;
import Spc;
import TestSpc;


void runKernel() {

    // GUI
    P.Num.Board = 1;
	P.Num.Det = 1;
	P.Chann.Num = 1024;
	P.Spc.Type = "TEST";
    P.Spc.Factor = 1.0; // ps/bin
	P.Spc.TimeO = 0.1; // s
	P.Spc.TimeM = 1.0; // s
    P.Contest.Function = CONTEST_OSC;

    // define variables
    std::unique_ptr<Step> steps[MAX_STEP];
    std::unique_ptr<Spc> spc[1];
    //std::vector<long> Data(P.Chann.Num);
    InitData();

    // update all GUI
    GUI->readAll();

    // display Output
    GUI->displayPanel("Output");

    // InitLoop
    for(int iL=0;iL<5;iL++) P.Loop[iL].Num=(P.Loop[iL].Last-P.Loop[iL].First)/P.Loop[iL].Delta+1;

	 //InitSteps
    for (int iS = 0; iS < MAX_STEP; ++iS) {
        steps[iS] = Step::createStep(iS);
        if(steps[iS]) steps[iS]->initStep();
        if(steps[iS]) steps[iS]->initPos();
        }

	// InitSpc
    spc[0] = Spc::createSpc();
    if (spc[0]) spc[0]->init();

    for (P.Loop[0].Actual = P.Loop[0].First; P.Loop[0].Actual <= P.Loop[0].Last; P.Loop[0].Actual += P.Loop[0].Delta) {
        for (P.Loop[1].Actual = P.Loop[1].First; P.Loop[1].Actual <= P.Loop[1].Last; P.Loop[1].Actual += P.Loop[1].Delta) {
            for (P.Loop[2].Actual = P.Loop[2].First; P.Loop[2].Actual <= P.Loop[2].Last; P.Loop[2].Actual += P.Loop[2].Delta) {
                for (P.Loop[3].Actual = P.Loop[3].First; P.Loop[3].Actual <= P.Loop[3].Last; P.Loop[3].Actual += P.Loop[3].Delta) {
                    for (P.Loop[4].Actual = P.Loop[4].First; P.Loop[4].Actual <= P.Loop[4].Last; P.Loop[4].Actual += P.Loop[4].Delta) {
                        bool status=false;

                        for (auto& s : steps) {  
                            if (s) s->moveStep(&s->actual, s->calcGoal(), P.Step[s->iS].Mode != "MULTI", status);  
                        }
                        if (spc[0]) {
                            spc[0]->wait();
                            spc[0]->get();
                        }

                        outText(std::format("Loop = {}", P.Loop[4].Actual));

                        std::vector<double> t(static_cast<size_t>(P.Chann.Num));
                        for (int i = 0; i < P.Chann.Num; ++i)
                            t[static_cast<size_t>(i)] = (static_cast<double>(i) + 0.5) * P.Spc.Factor;

                        // Plot all points at once
                        if (GUI) GUI->displayPlot(t, Data);


                    }
                }
            }
        }
    }
    displayPanel("Parm");
}
