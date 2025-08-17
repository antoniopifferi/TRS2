#include <iostream>
#include <memory>
#include <vector>

#include "GenSource/runKernel.h"
//#include "GenSource/Parm.h"
//#include "GenSource/Var.h"

import Const;
import Globals;
import Step;




void runKernel() {
    std::unique_ptr<Step> steps[MAX_STEP];

    // InitLoop
    for(int iL=0;iL<5;iL++) P.Loop[iL].Num=(P.Loop[iL].Last-P.Loop[iL].First)/P.Loop[iL].Delta+1;

	// InitSteps
  for (int iS = 0; iS < MAX_STEP; ++iS) {
        steps[iS] = Step::createStep(iS);
 //       if(steps[iS]) steps[iS]->initStep();
 //       if(steps[iS]) steps[iS]->initPos();
        }

 //   for (P.Loop[0].Actual = P.Loop[0].First; P.Loop[0].Actual <= P.Loop[0].Last; P.Loop[0].Actual += P.Loop[0].Delta) {
 //       for (P.Loop[1].Actual = P.Loop[1].First; P.Loop[1].Actual <= P.Loop[1].Last; P.Loop[1].Actual += P.Loop[1].Delta) {
 //           for (P.Loop[2].Actual = P.Loop[2].First; P.Loop[2].Actual <= P.Loop[2].Last; P.Loop[2].Actual += P.Loop[2].Delta) {
 //               for (P.Loop[3].Actual = P.Loop[3].First; P.Loop[3].Actual <= P.Loop[3].Last; P.Loop[3].Actual += P.Loop[3].Delta) {
 //                   for (P.Loop[4].Actual = P.Loop[4].First; P.Loop[4].Actual <= P.Loop[4].Last; P.Loop[4].Actual += P.Loop[4].Delta) {
 //                       bool status=false;

 //                       for (auto& s : steps) {  
 //                           if (s) s->moveStep(&s->actual, s->calcGoal(), P.Step[s->iS].Mode != "MULTI", status);  
 //                       }
 //                   }
 //               }
 //           }
 //       }
 //   }
}
