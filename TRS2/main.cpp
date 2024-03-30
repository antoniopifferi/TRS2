#include "trs2.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TRS2 w;
    w.show();
    return a.exec();
}
