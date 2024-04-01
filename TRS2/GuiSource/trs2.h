#ifndef TRS2_H
#define TRS2_H

#include <QMainWindow>
#include <QString>
#include <QMap>
#include <vector>

#define NUMLOOP 5

struct LoopS {
    int Home;
    int First;
    int Last;
    int Delta;
    int Num;
    QString FileBreak;
    bool Break;
    bool Invert;
    QString Cont;
};

struct ParmS {
    struct LoopS Loop[NUMLOOP];
};

struct TableS {
    QString Name;
    QString Type;
    void* Var;
    QObject* Obj;
};

QT_BEGIN_NAMESPACE
namespace Ui { class TRS2; }
QT_END_NAMESPACE

class TRS2 : public QMainWindow
{
    Q_OBJECT

public:
    TRS2(QWidget *parent = nullptr);
    ~TRS2();

private slots:
    void updateTFromUI();
    void printP();
    void addTab(QString Prefix, int Id, void* Var);
    void saveSet(QString FilePath);
    void loadSet(QString FilePath);
    void readAll();

private:
    Ui::TRS2 *ui;
    QMap<QString, void*> widgetToTMap;
    std::vector<TableS> T;
    ParmS P;
};
#endif // TRS2_H
