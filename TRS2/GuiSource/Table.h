#ifndef TABLE_H
#define TABLE_H

void TRS2::createTable() {

    // Loop
    for(int iL=0;iL<MAXLOOP;iL++){
        addTab("LoopHome", iL, &P.Loop[iL].Home);
        addTab("LoopFirst", iL, &P.Loop[iL].First);
        addTab("LoopLast", iL, &P.Loop[iL].Last);
        addTab("LoopDelta", iL, &P.Loop[iL].Delta);
        addTab("LoopNum", iL, &P.Loop[iL].Num);
        addTab("LoopFileBreak", iL, &P.Loop[iL].FileBreak);
        addTab("LoopBreak", iL, &P.Loop[iL].Break);
        addTab("LoopInvert", iL, &P.Loop[iL].Invert);
        addTab("LoopCont", iL, &P.Loop[iL].Cont);
    }

    // Step
    for(int iS=0;iS<MAX_STEP;iS++){
        addTab("StepType", iS, &P.Step[iS].Type);
        addTab("StepCom", iS, &P.Step[iS].Com);
        addTab("StepAxis", iS, &P.Step[iS].Axis);
        addTab("StepMode", iS, &P.Step[iS].Mode);
        addTab("StepSign", iS, &P.Step[iS].Sign);
        addTab("StepLoop", iS, &P.Step[iS].Loop);
        addTab("StepHold", iS, &P.Step[iS].Hold);
        addTab("StepLcd", iS, &P.Step[iS].Lcd);
        addTab("StepFName", iS, &P.Step[iS].FName);
        addTab("StepMin", iS, &P.Step[iS].Min);
        addTab("StepMax", iS, &P.Step[iS].Max);
        addTab("StepFreqMin", iS, &P.Step[iS].FreqMin);
        addTab("StepFreqMax", iS, &P.Step[iS].FreqMax);
        addTab("StepFreqDelta", iS, &P.Step[iS].FreqDelta);
        addTab("StepFreq", iS, &P.Step[iS].Freq);
        addTab("StepFactor", iS, &P.Step[iS].Factor);
        addTab("StepSort", iS, &P.Step[iS].Sort);
    }

}

#endif // TABLE_H
