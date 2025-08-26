#include "src/gui/trs2.h"
#include "src/run/runKernel.h"
#include "src/gui/ui_trs2.h"
#include "AppLogger.h"

#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPainter>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>

#include <typeinfo>
#include <algorithm>
#include <limits>

import Globals;
import Const;


// Always "<Prefix>_<1-based>"
template <class T>
bool bindIdx1(qtbind::Binder& b, const char* prefix, int zeroBasedIdx, T& var) {
    const QString name = QString::fromLatin1(prefix) + "_" + QString::number(zeroBasedIdx + 1);
    return b.bind(name, var);
}

TRS2::TRS2(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::TRS2)
{
    ui->setupUi(this);

    // Make the global GUI pointer available
    GUI = this;

    // set display panel from menu
    connect(ui->actionMeasure, &QAction::triggered, this, []() { runKernel(); });
    connect(ui->actionParm, &QAction::triggered, this, [this]() { displayPanel("Parm"); });
    connect(ui->actionStep, &QAction::triggered, this, [this]() { displayPanel("Step"); });
    connect(ui->actionOutput, &QAction::triggered, this, [this]() { displayPanel("Output"); });

    // Connect logger to the Output box (queued == thread-safe)
    connect(&AppLogger::instance(), &AppLogger::message, this, &TRS2::appendOutput, Qt::QueuedConnection);
    connect(&AppLogger::instance(), &AppLogger::showPanel, this, &TRS2::displayPanel, Qt::QueuedConnection);

    // Create binder
    binder_ = std::make_unique<qtbind::Binder>(ui->centralwidget);

    // === BINDINGS (underscore + 1-based) ==========================
    for (int iL = 0; iL < MAX_LOOP; ++iL) {
        bindIdx1(*binder_, "LoopHome", iL, P.Loop[iL].Home);
        bindIdx1(*binder_, "LoopFirst", iL, P.Loop[iL].First);
        bindIdx1(*binder_, "LoopLast", iL, P.Loop[iL].Last);
        bindIdx1(*binder_, "LoopDelta", iL, P.Loop[iL].Delta);
        bindIdx1(*binder_, "LoopNum", iL, P.Loop[iL].Num);
        bindIdx1(*binder_, "LoopFileBreak", iL, P.Loop[iL].FileBreak);
        bindIdx1(*binder_, "LoopBreak", iL, P.Loop[iL].Break);
        bindIdx1(*binder_, "LoopInvert", iL, P.Loop[iL].Invert);
        bindIdx1(*binder_, "LoopCont", iL, P.Loop[iL].Cont);
    }

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
    // ===============================================================

    // LOAD SETTINGS (INI, as requested)
    loadIni("c:\\Temp\\TRS2.ini");

    // READ ALL
    readAll();

    // === CHART SETUP (DisplayPlot placeholder in .ui) ==============
    plotContainer_ = this->findChild<QWidget*>("displayPlot");
    if (!plotContainer_) {
        qWarning() << "DisplayPlot widget not found in .ui. Please add a QWidget named 'DisplayPlot'.";
    }
    else {
        if (!plotContainer_->layout()) {
            auto* v = new QVBoxLayout(plotContainer_);
            v->setContentsMargins(0, 0, 0, 0);
            plotContainer_->setLayout(v);
        }

        chart_ = new QtCharts::QChart();
        chart_->setTitle(QStringLiteral("Scatter: y=Data (log) vs x=t"));

        series_ = new QtCharts::QScatterSeries();
        series_->setMarkerSize(6.0);
        series_->setName(QStringLiteral("Data(t)"));

        chart_->addSeries(series_);

        axisX_ = new QtCharts::QValueAxis();
        axisX_->setTitleText(QStringLiteral("t"));
        axisX_->setLabelFormat("%.3g");
        chart_->addAxis(axisX_, Qt::AlignBottom);
        series_->attachAxis(axisX_);

        axisY_ = new QtCharts::QLogValueAxis();
        axisY_->setBase(10.0);
        axisY_->setMinorTickCount(9); // nice decades
        axisY_->setLabelFormat("%.0e");
        axisY_->setTitleText(QStringLiteral("Data"));
        chart_->addAxis(axisY_, Qt::AlignLeft);
        series_->attachAxis(axisY_);

        chartView_ = new QtCharts::QChartView(chart_, plotContainer_);
        chartView_->setRenderHint(QPainter::Antialiasing, true);
        plotContainer_->layout()->addWidget(chartView_);
    }
    // ===============================================================
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

void TRS2::displayPanel(const QString& namePanel)
{
    QWidget* widget = ui->stackedWidget->findChild<QWidget*>(namePanel);
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

// === NEW: refresh whole scatter in one shot ===
void TRS2::plot(const std::vector<long>& Data, const std::vector<long>& t)
{
    if (!series_ || !axisX_ || !axisY_) return;

    const std::size_t n = std::min(Data.size(), t.size());
    if (n == 0) {
        series_->clear();
        return;
    }

    QVector<QPointF> pts;
    pts.reserve(static_cast<int>(n));

    double xmin = std::numeric_limits<double>::infinity();
    double xmax = -std::numeric_limits<double>::infinity();
    double ymin = std::numeric_limits<double>::infinity(); // strictly positive
    double ymax = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        const double x = static_cast<double>(t[i]);
        const double y = static_cast<double>(Data[i]);

        // Log axis cannot display y<=0. Skip non-positive values.
        if (y > 0.0) {
            pts.push_back(QPointF(x, y));
            xmin = std::min(xmin, x);
            xmax = std::max(xmax, x);
            ymin = std::min(ymin, y);
            ymax = std::max(ymax, y);
        }
    }

    // Replace the whole dataset at once (fast path)
    series_->replace(pts);

    // Handle degenerate cases gracefully
    if (!pts.isEmpty()) {
        if (xmin == xmax) { xmin -= 0.5; xmax += 0.5; }
        axisX_->setRange(xmin, xmax);

        // keep y strictly positive and not identical
        if (ymin <= 0.0 || !std::isfinite(ymin)) ymin = 1.0;
        if (ymax <= ymin) ymax = ymin * 10.0;

        axisY_->setRange(ymin, ymax);
    }
    else {
        // No positive values: show a neutral log range and x range from t
        double txmin = static_cast<double>(t.front());
        double txmax = static_cast<double>(t.back());
        if (txmin == txmax) { txmin -= 0.5; txmax += 0.5; }
        axisX_->setRange(txmin, txmax);
        axisY_->setRange(1.0, 10.0);
    }

    // Ensure immediate visual update
    chart_->update();
    if (chartView_) chartView_->viewport()->update();
}
