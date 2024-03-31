#include "trs2.h"
#include "ui_trs2.h"

TRS2::TRS2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TRS2)
{
    ui->setupUi(this);
}

TRS2::~TRS2()
{
    delete ui;
}

