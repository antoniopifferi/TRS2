#include "src/gui/trs2.h"  
#include <QApplication>  

import Globals;

int main(int argc, char *argv[])  
{  
    QApplication a(argc, argv);  
    TRS2 w;                   // create the window after QApplication
    GUI = &w;                 // publish it to the world
    w.show();  
    return a.exec();  
}