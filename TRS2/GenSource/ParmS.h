#ifndef PARMS_H
#define PARMS_H

#define NUMLOOP 5

#include <QMainWindow>
#include <QString>
#include <QMap>
#include <vector>

struct LoopS {
    int Home;
    int First;
    int Last;
    int Delta;
    int Num;
    int Actual;
    QString FileBreak;
    bool Break;
    bool Invert;
    QString Cont;
};

struct ParmS {
    struct LoopS Loop[NUMLOOP];
};

extern ParmS P;

#endif // PARMS_H
