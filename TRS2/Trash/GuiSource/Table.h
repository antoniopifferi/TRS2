#ifndef TABLE_H
#define TABLE_H

import Const;
import Globals;

inline void TRS2::createTable() {

    // Loop
    for(int iL=0;iL<MAX_LOOP;iL++){
        addTab("LoopHome", iL, &P.Loop[iL].Home, typeid(int));
        addTab("LoopFirst", iL, &P.Loop[iL].First, typeid(int));
        addTab("LoopLast", iL, &P.Loop[iL].Last, typeid(int));
        addTab("LoopDelta", iL, &P.Loop[iL].Delta, typeid(int));
        addTab("LoopNum", iL, &P.Loop[iL].Num, typeid(int));
        addTab("LoopFileBreak", iL, &P.Loop[iL].FileBreak[0], typeid(QString));
        addTab("LoopBreak", iL, &P.Loop[iL].Break, typeid(int));
        addTab("LoopInvert", iL, &P.Loop[iL].Invert, typeid(int));
        addTab("LoopCont", iL, &P.Loop[iL].Cont, typeid(int));
    }

    // Step
    for(int iS=0;iS<MAX_STEP;iS++){
        addTab("StepType", iS, &P.Step[iS].Type, typeid(int));
        addTab("StepCom", iS, &P.Step[iS].Com, typeid(int));
        addTab("StepAxis", iS, &P.Step[iS].Axis, typeid(int));
        addTab("StepMode", iS, &P.Step[iS].Mode, typeid(int));
        addTab("StepSign", iS, &P.Step[iS].Sign, typeid(int));
        addTab("StepLoop", iS, &P.Step[iS].Loop, typeid(int));
        addTab("StepHold", iS, &P.Step[iS].Hold, typeid(int));
        addTab("StepLcd", iS, &P.Step[iS].Lcd, typeid(P.Step[iS].Lcd));
        addTab("StepFName", iS, &P.Step[iS].FName[0], typeid(QString));
        addTab("StepMin", iS, &P.Step[iS].Min, typeid(int));
        addTab("StepMax", iS, &P.Step[iS].Max, typeid(int));
        addTab("StepFreqMin", iS, &P.Step[iS].FreqMin, typeid(int));
        addTab("StepFreqMax", iS, &P.Step[iS].FreqMax, typeid(int));
        addTab("StepFreqDelta", iS, &P.Step[iS].FreqDelta, typeid(int));
        addTab("StepFreq", iS, &P.Step[iS].Freq, typeid(int));
        addTab("StepFactor", iS, &P.Step[iS].Factor, typeid(double));
        addTab("StepSort", iS, &P.Step[iS].Sort, typeid(int));
    }

}

#endif // TABLE_H
