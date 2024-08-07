#include <iostream>
#include "DevSource/MicroStep.h"
#include "GenSource/runKernel.h"
#include "GenSource/Step.h"
#include "GenSource/Parm.h"

void runKernel() {
    for (int iS=0;iS<MAXSTEP;iS++) P.Step[iS].Type="Micro";
        Step* step1 = new MicroStep(1); // Polymorphic usage
    //Step* step1=Step::createStep(1);
//    Step* step1=Step::createStep(1);

    for (P.Loop[0].Actual = P.Loop[0].First; P.Loop[0].Actual <= P.Loop[0].Last; P.Loop[0].Actual += P.Loop[0].Delta) {
        for (P.Loop[1].Actual = P.Loop[1].First; P.Loop[1].Actual <= P.Loop[1].Last; P.Loop[1].Actual += P.Loop[1].Delta) {
            for (P.Loop[2].Actual = P.Loop[2].First; P.Loop[2].Actual <= P.Loop[2].Last; P.Loop[2].Actual += P.Loop[2].Delta) {
                for (P.Loop[3].Actual = P.Loop[3].First; P.Loop[3].Actual <= P.Loop[3].Last; P.Loop[3].Actual += P.Loop[3].Delta) {
                    for (P.Loop[4].Actual = P.Loop[4].First; P.Loop[4].Actual <= P.Loop[4].Last; P.Loop[4].Actual += P.Loop[4].Delta) {
                        long actual=0;
                        long goal=100;
                        int step=0;
                        bool wait=false;
                        bool status=false;
                        step1->moveStep(&actual,goal,step,wait,status);
                    }
                }
            }
        }
    }
}
