#ifndef TRS2_H
#define TRS2_H

#include <QMainWindow>
#include <memory>
#include <vector>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>


#include "src/gui/Binder.h"    // existing binder
QT_BEGIN_NAMESPACE
namespace Ui { class TRS2; }
QT_END_NAMESPACE

// Forward decls for QtCharts types (pointers are fine here)
namespace QtCharts {
    class QChart;
    class QChartView;
    class QScatterSeries;
    class QValueAxis;
    class QLogValueAxis;
}

class TRS2 : public QMainWindow
{
    Q_OBJECT
public:
    explicit TRS2(QWidget* parent = nullptr);
    ~TRS2();

    void readAll();
    void writeAll();
    void readSingle(const QString& name);
    void writeSingle(const QString& name);
    void saveIni(const QString& path);
    void loadIni(const QString& path);
    void appendOutput(const QString& msg);
    void displayPanel(const QString& namePanel);

    // Called from runKernel: refresh whole scatter in one call
    void plot(const std::vector<long>& Data, const std::vector<long>& t);

private:
    Ui::TRS2* ui = nullptr;
    std::unique_ptr<qtbind::Binder> binder_;

    // Chart members
    QWidget* plotContainer_ = nullptr;
    QtCharts::QChart* chart_ = nullptr;
    QtCharts::QChartView* chartView_ = nullptr;
    QtCharts::QScatterSeries* series_ = nullptr;
    QtCharts::QValueAxis* axisX_ = nullptr;
    QtCharts::QLogValueAxis* axisY_ = nullptr;
};

#endif // TRS2_H
