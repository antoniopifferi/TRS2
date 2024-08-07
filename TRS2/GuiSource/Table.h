#ifndef TABLE_H
#define TABLE_H

void TRS2::createTable() {
    for(int il=0;il<MAXLOOP;il++){
        addTab("LoopHome", il, &P.Loop[il].Home);
        addTab("LoopFirst", il, &P.Loop[il].First);
        addTab("LoopLast", il, &P.Loop[il].Last);
        addTab("LoopDelta", il, &P.Loop[il].Delta);
        addTab("LoopNum", il, &P.Loop[il].Num);
        addTab("LoopFileBreak", il, &P.Loop[il].FileBreak);
        addTab("LoopBreak", il, &P.Loop[il].Break);
        addTab("LoopInvert", il, &P.Loop[il].Invert);
        addTab("LoopCont", il, &P.Loop[il].Cont);
    }
}

#endif // TABLE_H
