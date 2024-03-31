#ifndef TEST5_H
#define TEST5_H

#include <QMainWindow>
#include <QString>
#include <QMap>
#include <vector>

struct ParmS {
    int vInt[2];
    double vDouble[2];
    QString vString[2];
    QString vCombo[2];
    bool vCheck[2];
};

struct TableS {
    QString Name;
    QString Type;
    void* Var;
};

QT_BEGIN_NAMESPACE
namespace Ui { class Test5; }
QT_END_NAMESPACE

class Test5 : public QMainWindow
{
    Q_OBJECT

public:
    Test5(QWidget *parent = nullptr);
    ~Test5();

private slots:
    void updateTFromUI();
    void printP();
    void addTab(QString Prefix, int Id, void* Var);
    void saveSet(QString FilePath);
    void loadSet(QString FilePath);

private:
    Ui::Test5 *ui;
    QMap<QString, void*> widgetToTMap;
    std::vector<TableS> T;
    ParmS P;
};

#endif // TEST5_H
