#include "src/gui/trs2.h"
#include "src/run/runKernel.h"
#include "ui_trs2.h"
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
#include <QCoreApplication>
#include <QDir>

#include <typeinfo>
#include <algorithm>
#include <limits>

// Always "<Prefix>_<1-based>"
template <class T>
bool bindIdx1(qtbind::Binder& b, const char* prefix, int zeroBasedIdx, T& var) {
    const QString name = QString::fromLatin1(prefix) + "_" + QString::number(zeroBasedIdx + 1);
    return b.bind(name, var);
}

// Always "<Prefix>_<1-based>"
template <class T>
bool bindIdx1(qtbind::Binder& b, const char* prefix, T& var) {
    const QString name = QString::fromLatin1(prefix);
    return b.bind(name, var);
}

static QString findProjectRoot()
{
    QDir dir(QCoreApplication::applicationDirPath());
    // Walk up until we find CMakeLists.txt or reach filesystem root
    while (true) {
        if (QFile::exists(dir.filePath("CMakeLists.txt")))
            return dir.absolutePath();
        if (!dir.cdUp())
            break;
    }
    return QCoreApplication::applicationDirPath();
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
    connect(ui->actionMharp, &QAction::triggered, this, [this]() { displayPanel("Mharp"); });

    // Connect logger to the Output box (queued == thread-safe)
    connect(&AppLogger::instance(), &AppLogger::message,this, &TRS2::appendOutput,Qt::QueuedConnection);
    connect(&AppLogger::instance(), &AppLogger::showPanel, this, &TRS2::displayPanel, Qt::QueuedConnection);


    // Create binder
    binder_ = std::make_unique<qtbind::Binder>(ui->centralwidget);

    // === BINDINGS (underscore + 1-based) ==========================
    
    // FILE
	bindIdx1(*binder_, "FileType", P.File.Type);
	bindIdx1(*binder_, "FileDir", P.File.Dir);
	bindIdx1(*binder_, "FilePrefix", P.File.Prefix);
	bindIdx1(*binder_, "FileExt", P.File.Ext);
	bindIdx1(*binder_, "FileTag", P.File.Tag);
	bindIdx1(*binder_, "FileSave", P.File.Save);
    
    // SPC
	bindIdx1(*binder_, "SpcType", P.Spc.Type);
	bindIdx1(*binder_, "SpcWait", P.Wait.Type);
	bindIdx1(*binder_, "SpcTimeM", P.Spc.TimeM);
    bindIdx1(*binder_, "SpcTimeO", P.Spc.TimeO);
	bindIdx1(*binder_, "SpcFactor", P.Spc.Factor);
	bindIdx1(*binder_, "SpcCount", P.Spc.Count);
	bindIdx1(*binder_, "SpcChrono", P.Chrono.Delta);
    bindIdx1(*binder_, "SpcSpc1", P.Spc.IniFile[0]);
	bindIdx1(*binder_, "SpcSpc2", P.Spc.IniFile[1]);
	bindIdx1(*binder_, "SpcSpc3", P.Spc.IniFile[2]);
	bindIdx1(*binder_, "SpcSpc4", P.Spc.IniFile[3]);

	// CHAN
	bindIdx1(*binder_, "ChanFirst", P.Chann.First);
	bindIdx1(*binder_, "ChanLast", P.Chann.Last);
	bindIdx1(*binder_, "ChanNum", P.Chann.Num);

    // LOOP
    for (int iL = 0; iL < MAX_LOOP; ++iL) {
        bindIdx1(*binder_, "LoopHome", iL, P.Loop[iL].Home);
        bindIdx1(*binder_, "LoopFirst", iL, P.Loop[iL].First);
        bindIdx1(*binder_, "LoopLast", iL, P.Loop[iL].Last);
        bindIdx1(*binder_, "LoopDelta", iL, P.Loop[iL].Delta);
        bindIdx1(*binder_, "LoopNum", iL, P.Loop[iL].Num);
        bindIdx1(*binder_, "LoopFileBreak", iL, P.Loop[iL].FileBreak);
        bindIdx1(*binder_, "LoopBreak", iL, P.Loop[iL].Break);
        bindIdx1(*binder_, "LoopInvert", iL, P.Loop[iL].Invert);
        bindIdx1(*binder_, "LoopCont",     iL, P.Loop[iL].Cont);
    }
    
    // STEP
    for (int iS = 0; iS < MAX_STEP; ++iS) {
        bindIdx1(*binder_, "StepType", iS, P.Step[iS].Type);
        bindIdx1(*binder_, "StepCom", iS, P.Step[iS].Com);
        bindIdx1(*binder_, "StepAxis", iS, P.Step[iS].Axis);
        bindIdx1(*binder_, "StepMode", iS, P.Step[iS].Mode);
        bindIdx1(*binder_, "StepSign", iS, P.Step[iS].Sign);
        bindIdx1(*binder_, "StepLoop", iS, P.Step[iS].Loop);
        bindIdx1(*binder_, "StepHold", iS, P.Step[iS].Hold);
        bindIdx1(*binder_, "StepLcd", iS, P.Step[iS].Lcd);
        bindIdx1(*binder_, "StepFName", iS, P.Step[iS].FName);
        bindIdx1(*binder_, "StepMin", iS, P.Step[iS].Min);
        bindIdx1(*binder_, "StepMax", iS, P.Step[iS].Max);
        bindIdx1(*binder_, "StepFreqMin", iS, P.Step[iS].FreqMin);
        bindIdx1(*binder_, "StepFreqMax", iS, P.Step[iS].FreqMax);
        bindIdx1(*binder_, "StepFreqDelta", iS, P.Step[iS].FreqDelta);
        bindIdx1(*binder_, "StepFreq", iS, P.Step[iS].Freq);
        bindIdx1(*binder_, "StepFactor", iS, P.Step[iS].Factor);
        bindIdx1(*binder_, "StepSort", iS, P.Step[iS].Sort);
    }

    // MHARP (scalar controls, optional if present in UI)
    bindIdx1(*binder_, "MharpBinning", P.Spc.Mharp[0].Binning);
    bindIdx1(*binder_, "MharpSyncDivider", P.Spc.Mharp[0].SyncDivider);
    bindIdx1(*binder_, "MharpLenCode", P.Spc.Mharp[0].LenCode);
    bindIdx1(*binder_, "MharpOffset", P.Spc.Mharp[0].Offset);
    bindIdx1(*binder_, "MharpSyncOffset", P.Spc.Mharp[0].SyncOffset);
    bindIdx1(*binder_, "MharpSyncLevel", P.Spc.Mharp[0].SyncLevel);
    bindIdx1(*binder_, "MharpSyncEdge", P.Spc.Mharp[0].SyncEdge);
    bindIdx1(*binder_, "MharpSaveTags", P.Spc.Mharp[0].SaveTags);
    bindIdx1(*binder_, "MharpPathTags", P.Spc.Mharp[0].PathTags);

    // LOAD SETTINGS (INI) relative to project root (folder containing CMakeLists.txt)
    loadIni(QDir(findProjectRoot()).filePath("SET/TRS2.TRS"));

    // READ ALL
    readAll();

}

TRS2::~TRS2()
{
    saveIni(QDir(findProjectRoot()).filePath("SET/TRS2.TRS"));
    delete ui;
}

void TRS2::readAll() {
    if (binder_) binder_->readAll();
}

void TRS2::writeAll() {
    if (binder_) binder_->writeAll();
}

void TRS2::readSingle(const QString& name) {
    if (binder_) binder_->readSingle(name);
}

void TRS2::writeSingle(const QString& name) {
    if (binder_) binder_->writeSingle(name);
}

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

void TRS2::appendOutput(const QString& msg)
{
    ui->outputText->appendPlainText(msg);
}

void TRS2::displayPlot(const std::vector<double>& X,
    const std::vector<long>& Y)
{
    if (!ui || !ui->displayPlot) return;

    QCPGraph* g = nullptr;
    if (ui->displayPlot->graphCount() == 0) {
        g = ui->displayPlot->addGraph();
        g->setLineStyle(QCPGraph::lsNone);
        g->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));

        ui->displayPlot->xAxis->setLabel("time (ps)");
        ui->displayPlot->xAxis->setScaleType(QCPAxis::stLinear);

        ui->displayPlot->yAxis->setLabel("counts");
        ui->displayPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);
        QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
        ui->displayPlot->yAxis->setTicker(logTicker);
        ui->displayPlot->yAxis->setNumberFormat("eb");
        ui->displayPlot->yAxis->setNumberPrecision(0);
    }
    else {
        g = ui->displayPlot->graph(0);
    }

    const int n = static_cast<int>(std::min(X.size(), Y.size()));
    QVector<double> qx; qx.reserve(n);
    QVector<double> qy; qy.reserve(n);

    for (int i = 0; i < n; ++i) {
        const double xi = X[i];
        double yi = static_cast<double>(Y[i]);

        if (yi <= 0.0) yi = 0.001;

        qx.push_back(xi);
        qy.push_back(yi);
    }

    g->setData(qx, qy, true);

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
            ui->displayPlot->yAxis->setRange(1, ymax);
        }
        else {
            ui->displayPlot->yAxis->setRange(1.0, 10.0);
        }
    }

    ui->displayPlot->replot(QCustomPlot::rpQueuedReplot);
}
