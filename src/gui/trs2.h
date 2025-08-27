#ifndef TRS2_H
#define TRS2_H

#include <QMainWindow>
#include <QString>
#include <QMap>
#include <vector>
#include <typeindex>

#include "src/gui/Binder.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TRS2; }
QT_END_NAMESPACE

class TRS2 : public QMainWindow
{
    Q_OBJECT

public:
    TRS2(QWidget *parent = nullptr);
    ~TRS2();
    void readAll();                          // widgets -> vars
    void displayPanel(const QString& namePanel);
    void writeAll();                         // vars -> widgets
    void readSingle(const QString& name);    // one widget -> vars
    void writeSingle(const QString& name);   // vars -> one widget
    void saveIni(const QString& path);
    void loadIni(const QString& path);
    void appendOutput(const QString& msg);
    void displayPlot(const std::vector<double>& X, const std::vector<long>& Y);

private slots:

private:
    Ui::TRS2 *ui;
    std::unique_ptr<qtbind::Binder> binder_;
};
#endif // TRS2_H
