#ifndef TRS2_H
#define TRS2_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TRS2; }
QT_END_NAMESPACE

class TRS2 : public QMainWindow
{
    Q_OBJECT

public:
    TRS2(QWidget *parent = nullptr);
    ~TRS2();

private:
    Ui::TRS2 *ui;
};
#endif // TRS2_H
