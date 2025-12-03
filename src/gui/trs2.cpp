#include "src/gui/trs2.h"
#include "src/run/runKernel.h"
#include "ui_trs2.h"
//#include "GenSource/Parm.h"
//#include "GuiSource/Table.h"
#include "AppLogger.h"
#include "lib/qcustomplot.h"

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
#include <algorithm>
#include <limits>

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
    connect(&AppLogger::instance(), &AppLogger::showPanel, this, &TRS2::displayPanel, Qt::QueuedConnection);


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

// trs2.cpp
void TRS2::displayPlot(const std::vector<double>& X,
    const std::vector<long>& Y)
{
    if (!ui || !ui->displayPlot) return;

    // Create the first graph if missing and configure once.
    QCPGraph* g = nullptr;
    if (ui->displayPlot->graphCount() == 0) {
        g = ui->displayPlot->addGraph();
        g->setLineStyle(QCPGraph::lsNone); // markers only, no line
        g->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));

        // Axes and labels
        ui->displayPlot->xAxis->setLabel("time (ps)");
        ui->displayPlot->xAxis->setScaleType(QCPAxis::stLinear);

        ui->displayPlot->yAxis->setLabel("counts");
        ui->displayPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);
        QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
        ui->displayPlot->yAxis->setTicker(logTicker);
        ui->displayPlot->yAxis->setNumberFormat("eb");   // e.g. 1e3
        ui->displayPlot->yAxis->setNumberPrecision(0);
    }
    else {
        g = ui->displayPlot->graph(0);
    }

    // Convert to QVector and sanitize Y for log scale (skip non-positive).
    const int n = static_cast<int>(std::min(X.size(), Y.size()));
    QVector<double> qx; qx.reserve(n);
    QVector<double> qy; qy.reserve(n);

    for (int i = 0; i < n; ++i) {
        const double xi = X[i];
        double yi = static_cast<double>(Y[i]);

        // For log axis: ensure strictly positive.
        // Here we clamp everything <= 0 up to 1.
        if (yi <= 0.0) yi = 0.001;

        qx.push_back(xi);
        qy.push_back(yi);
    }

    // One-shot refresh of all points
    g->setData(qx, qy, /*alreadySorted=*/true);

    // Ranges
    if (!qx.isEmpty()) {
        auto [xminIt, xmaxIt] = std::minmax_element(qx.begin(), qx.end());
        double xmin = std::isfinite(*xminIt) ? *xminIt : 0.0;
        double xmax = std::isfinite(*xmaxIt) ? *xmaxIt : 1.0;
        if (xmin == xmax) xmax = xmin + 1.0;
        ui->displayPlot->xAxis->setRange(xmin, xmax);

        double ymin = std::numeric_limits<double>::infinity();
        double ymax = 0.0;
        for (double v : qy) if (std::isfinite(v) && v > 0) {
            ymin = std::min(ymin, v);
            ymax = std::max(ymax, v);
        }
        if (std::isfinite(ymin) && ymax > 0) {
            //ui->displayPlot->yAxis->setRange(ymin, ymax);
            ui->displayPlot->yAxis->setRange(1, ymax);
        }
        else {
            ui->displayPlot->yAxis->setRange(1.0, 10.0); // fallback
        }
    }

    ui->displayPlot->replot(QCustomPlot::rpQueuedReplot);
}
