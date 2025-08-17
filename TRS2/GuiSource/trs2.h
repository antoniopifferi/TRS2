#ifndef TRS2_H
#define TRS2_H

#include <QMainWindow>
#include <QString>
#include <QMap>
#include <vector>
#include <typeindex>

struct TableS {
    QString Name;
    QString Type;
    void* Var;
    QObject* Obj;
    std::type_index TypeVar{ typeid(void) };   // store the type of Var
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
    void addTab(QString Prefix, int Id, void* Var, std::type_index TypeVar);
    void saveSet(QString FilePath);
    void loadSet(QString FilePath);
    void readAll();
    void displayPanel(const QString &namePanel);
    void createTable();
    void completeTable();
    void appendOutput(const QString& msg);

private:
    Ui::TRS2 *ui;
    QMap<QString, void*> widgetToTMap;
    std::vector<TableS> T;
};
#endif // TRS2_H
