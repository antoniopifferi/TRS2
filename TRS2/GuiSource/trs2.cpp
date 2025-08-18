#include "GuiSource/trs2.h"
#include "GenSource/runKernel.h"
#include "ui_trs2.h"
//#include "GenSource/Parm.h"
//#include "GuiSource/Table.h"
#include "AppLogger.h"

import Globals;
import Const;

#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include <typeinfo>

// Always "<Prefix>_<1-based>"
template <class T>
bool bindIdx1(qtbind::Binder& b, const char* prefix, int zeroBasedIdx, T& var) {
    const QString name = QString::fromLatin1(prefix) + "_" + QString::number(zeroBasedIdx + 1);
    return b.bind(name, var);
}


TRS2::TRS2(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::TRS2)
{
    ui->setupUi(this);

    // set display panel from menu
    connect(ui->actionMeasure, &QAction::triggered, this, []() { runKernel(); });
    connect(ui->actionParm, &QAction::triggered, this, [this]() { displayPanel("Parm"); });
    connect(ui->actionStep, &QAction::triggered, this, [this]() { displayPanel("Step"); });
    connect(ui->actionOutput, &QAction::triggered, this, [this]() { displayPanel("Output"); });

    // Connect logger to the Output box (queued == thread-safe)
    connect(&AppLogger::instance(), &AppLogger::message,this, &TRS2::appendOutput,Qt::QueuedConnection);


    // Create binder
    binder_ = std::make_unique<qtbind::Binder>(ui->centralwidget);

    // === BINDINGS (underscore + 1-based) ==========================
    // LOOP
    for (int iL = 0; iL < MAX_LOOP; ++iL) {
        bindIdx1(*binder_, "LoopHome", iL, P.Loop[iL].Home);
        bindIdx1(*binder_, "LoopFirst", iL, P.Loop[iL].First);
        bindIdx1(*binder_, "LoopLast", iL, P.Loop[iL].Last);
        bindIdx1(*binder_, "LoopDelta", iL, P.Loop[iL].Delta);
        bindIdx1(*binder_, "LoopNum", iL, P.Loop[iL].Num);
        bindIdx1(*binder_, "LoopFileBreak", iL, P.Loop[iL].FileBreak);   // QString (QLineEdit)
        bindIdx1(*binder_, "LoopBreak", iL, P.Loop[iL].Break);       // bool (QCheckBox)
        bindIdx1(*binder_, "LoopInvert", iL, P.Loop[iL].Invert);      // bool
        // LoopCont: choose one style — index (int) or label (QString):
        // bindIdx1(*binder_, "LoopCont",     iL, P.Loop[iL].LoopContIndex);   // int (QComboBox index)
        bindIdx1(*binder_, "LoopCont",     iL, P.Loop[iL].Cont);            // QString (QComboBox text)
    }
    // Mirrors your old Loop table list. :contentReference[oaicite:6]{index=6}
    
    // STEP
    for (int iS = 0; iS < MAX_STEP; ++iS) {
        // Keep as int (index) if that’s how you used them before:
        bindIdx1(*binder_, "StepType", iS, P.Step[iS].Type);
        bindIdx1(*binder_, "StepCom", iS, P.Step[iS].Com);
        bindIdx1(*binder_, "StepAxis", iS, P.Step[iS].Axis);
        bindIdx1(*binder_, "StepMode", iS, P.Step[iS].Mode);   
        bindIdx1(*binder_, "StepSign", iS, P.Step[iS].Sign);   
        bindIdx1(*binder_, "StepLoop", iS, P.Step[iS].Loop);
        bindIdx1(*binder_, "StepHold", iS, P.Step[iS].Hold);        // bool
        bindIdx1(*binder_, "StepLcd", iS, P.Step[iS].Lcd);         // bool
        bindIdx1(*binder_, "StepFName", iS, P.Step[iS].FName);       // QString (QLineEdit)
        bindIdx1(*binder_, "StepMin", iS, P.Step[iS].Min);         // int (QSpinBox)
        bindIdx1(*binder_, "StepMax", iS, P.Step[iS].Max);         // int
        bindIdx1(*binder_, "StepFreqMin", iS, P.Step[iS].FreqMin);     // double (QDoubleSpinBox)
        bindIdx1(*binder_, "StepFreqMax", iS, P.Step[iS].FreqMax);     // double
        bindIdx1(*binder_, "StepFreqDelta", iS, P.Step[iS].FreqDelta);   // double
        bindIdx1(*binder_, "StepFreq", iS, P.Step[iS].Freq);        // double
        bindIdx1(*binder_, "StepFactor", iS, P.Step[iS].Factor);      // double
        bindIdx1(*binder_, "StepSort", iS, P.Step[iS].Sort);        // bool
    }
    // Matches your Step table entries. :contentReference[oaicite:7]{index=7}
    // ===============================================================


    // LOAD SETTINGS (INI, as requested)
    loadIni("c:\\Temp\\TRS2.ini");

    // READ ALL
    readAll();

    // PRINT P
    printP();

}

TRS2::~TRS2()
{
    saveIni("c:\\Temp\\TRS2.ini");
    delete ui;
}

// widgets -> variables
void TRS2::readAll() {
    if (binder_) binder_->readAll();
}

// variables -> widgets
void TRS2::writeAll() {
    if (binder_) binder_->writeAll();
}

// single widget -> variables
void TRS2::readSingle(const QString& name) {
    if (binder_) binder_->readSingle(name);
}

// variables -> single widget
void TRS2::writeSingle(const QString& name) {
    if (binder_) binder_->writeSingle(name);
}

// INI save/load
void TRS2::saveIni(const QString& path) {
    if (binder_) binder_->saveIni(path);
}

void TRS2::loadIni(const QString& path) {
    if (binder_) binder_->loadIni(path);
}

void TRS2::printP() {
    //qDebug() << "Loop2Num" << P.Loop[1].Num;
    //outText("Starting process...");
}


void TRS2::displayPanel(const QString &namePanel)
{
    QWidget *widget = ui->stackedWidget->findChild<QWidget*>(namePanel);
    if (widget) {
        int index = ui->stackedWidget->indexOf(widget);
        if (index != -1) {
            ui->stackedWidget->setCurrentIndex(index);
        }
    }
}

// Append output to the Output panel
void TRS2::appendOutput(const QString& msg)
{
    ui->outputText->appendPlainText(msg);
}