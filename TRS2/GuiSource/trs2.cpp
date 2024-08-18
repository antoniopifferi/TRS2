#include "GuiSource/trs2.h"
#include "GenSource/runKernel.h"
#include "ui_trs2.h"
#include "GenSource/Parm.h"
#include "GuiSource/Table.h"

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

TRS2::TRS2(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::TRS2)
{
    ui->setupUi(this);

    // set display panel from menu
    connect(ui->actionMeasure, &QAction::triggered, this, []() { runKernel(); });
    connect(ui->actionParm, &QAction::triggered, this, [this]() { displayPanel("Parm"); });
    connect(ui->actionStep, &QAction::triggered, this, [this]() { displayPanel("Step"); });

    // create and update Table
    createTable();
    completeTable();

    // Connect Signals for Widgets
    for (const auto& iT : T) {
        if (iT.Obj) {
            if (iT.Type == "QLineEdit") {
                connect(iT.Obj, SIGNAL(editingFinished()), this, SLOT(updateTFromUI()));
            } else if (iT.Type == "QSpinBox"){
                connect(iT.Obj, SIGNAL(valueChanged(int)), this, SLOT(updateTFromUI()));
            } else if (iT.Type == "QDoubleSpinBox") {
                connect(iT.Obj, SIGNAL(valueChanged(double)), this, SLOT(updateTFromUI()));
            } else if (iT.Type == "QComboBox") {
                connect(iT.Obj, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTFromUI()));
            } else if (iT.Type == "QCheckBox") {
                connect(iT.Obj, SIGNAL(clicked()), this, SLOT(updateTFromUI()));
            }
        } else {
            // Handle cases where the object with the specified name is not found
            qDebug() << "Object with name" << iT.Name << "not found.";
        }
    }

    // Connect Signals for Menu
    //connect(ui->actionKernel, &QAction::triggered, this, &TRS2::on_actionKernel_triggered);


    // LOAD SETTINGS
    loadSet("c:\\Temp\\TRS2.TRS");

    // READ ALL
    readAll();

    // PRINT P
    printP();

}

TRS2::~TRS2()
{
    saveSet("c:\\Temp\\TRS2.TRS");
    delete ui;
}

void TRS2::completeTable() {
    for (auto& iT : T) {
        QObject* obj = findChild<QObject*>(iT.Name);
        if (obj) {
            const QMetaObject* meta = obj->metaObject();
            iT.Type = meta->className();
            iT.Obj = obj;
        }
    }
}

void TRS2::updateTFromUI() {
    for (const auto& iT : T) {
        if (iT.Obj == sender()) {
            if (iT.Type == "QLineEdit") {
                *static_cast<QString*>(iT.Var) = qobject_cast<QLineEdit*>(iT.Obj)->text();
            } else if (iT.Type == "QSpinBox") {
                *static_cast<int*>(iT.Var) = qobject_cast<QSpinBox*>(iT.Obj)->value();
            } else if (iT.Type == "QDoubleSpinBox") {
                *static_cast<double*>(iT.Var) = qobject_cast<QDoubleSpinBox*>(iT.Obj)->value();
            } else if (iT.Type == "QComboBox") {
                std::string stringValue = qobject_cast<QComboBox*>(iT.Obj)->currentText().toStdString();
                *static_cast<std::string*>(iT.Var) = stringValue;
            } else if (iT.Type == "QCheckBox") {
                *static_cast<bool*>(iT.Var) = qobject_cast<QCheckBox*>(iT.Obj)->isChecked();
            }
            break;
        }
    }
}

void TRS2::readAll() {
    for (const auto& iT : T) {
        if (iT.Obj) {
            if (iT.Type == "QLineEdit") {
                *static_cast<QString*>(iT.Var) = qobject_cast<QLineEdit*>(iT.Obj)->text();
            } else if (iT.Type == "QSpinBox") {
                *static_cast<int*>(iT.Var) = qobject_cast<QSpinBox*>(iT.Obj)->value();
            } else if (iT.Type == "QDoubleSpinBox") {
                *static_cast<double*>(iT.Var) = qobject_cast<QDoubleSpinBox*>(iT.Obj)->value();
            } else if (iT.Type == "QComboBox") {
                std::string stringValue = qobject_cast<QComboBox*>(iT.Obj)->currentText().toStdString();
                *static_cast<std::string*>(iT.Var) = stringValue;
            } else if (iT.Type == "QCheckBox") {
                *static_cast<bool*>(iT.Var) = qobject_cast<QCheckBox*>(iT.Obj)->isChecked();
            }
        }
    }
}

void TRS2::printP() {
    qDebug() << "Loop2Num" << P.Loop[1].Num;
}

void TRS2::addTab(QString Prefix, int Id, void* Var) {
    QString Name;
    if(Id==-1) // just single element
        Name=Prefix;
    else
        Name=Prefix+"_"+QString::number(Id+1);

    QObject* obj = findChild<QObject*>(Name);
    if(obj==nullptr) QMessageBox::information(nullptr, "Error Creating GUI Table", "Object with name "+Name+" not found in GUI");
    const QMetaObject* meta = obj->metaObject();
    QString Type = meta->className();

    T.push_back({Name,Type,Var});
}

void TRS2::saveSet(QString FilePath){
    QFile file(FilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        // Write header if needed
        out << "Name\tValue\n";

        // Write data to the file
        for (const auto& iT : T) {
            out << iT.Name << "\t";

            // Check the type and cast accordingly
            QObject* obj = findChild<QObject*>(iT.Name);
            if (iT.Type == "QLineEdit"){
                out << qobject_cast<QLineEdit*>(obj)->text();
            } else if (iT.Type == "QSpinBox") {
                out << qobject_cast<QSpinBox*>(obj)->value();
            } else if (iT.Type == "QDoubleSpinBox") {
                out << qobject_cast<QDoubleSpinBox*>(obj)->value();
            } else if (iT.Type == "QComboBox") {
                out << qobject_cast<QComboBox*>(obj)->currentText();
            } else if (iT.Type == "QCheckBox") {
                out << qobject_cast<QCheckBox*>(obj)->isChecked();
            }
            out << "\n";
        }
        file.close();
        QMessageBox::information(nullptr, "File saved", "File saved successfully.");
    } else {
        QMessageBox::critical(nullptr, "Error", "Could not open the file for writing.");
    }
}

void TRS2::loadSet(QString FilePath) {
    QFile file(FilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        // Read and ignore the header line if present
        QString header = in.readLine(); // Read the header line
        // Assuming the header line contains "Name\tValue", ignore it

        // Read data from the file
        while (!in.atEnd()) {
            QString line = in.readLine(); // Read each line
            QStringList parts = line.split("\t"); // Split by tab delimiter

            if (parts.length() == 2) {
                QString name = parts[0]; // Name of the setting
                QString value = parts[1]; // Value of the setting

                // Find the corresponding widget by name
                QObject* obj = findChild<QObject*>(name);

                if (obj != nullptr) {
                    // Check the type and set the value accordingly
                    if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(obj)) {
                        lineEdit->setText(value);
                    } else if (QSpinBox* spinBox = qobject_cast<QSpinBox*>(obj)) {
                        spinBox->setValue(value.toInt());
                    } else if (QDoubleSpinBox* doubleSpinBox = qobject_cast<QDoubleSpinBox*>(obj)) {
                        doubleSpinBox->setValue(value.toDouble());
                    } else if (QComboBox* comboBox = qobject_cast<QComboBox*>(obj)) {
                        comboBox->setCurrentText(value);
                    } else if (QCheckBox* checkBox = qobject_cast<QCheckBox*>(obj)) {
                        checkBox->setChecked(value.toInt() != 0);
                    }
                } else {
                    // Handle cases where the object with the specified name is not found
                    qDebug() << "Object with name" << name << "not found.";
                }
            }
        }

        file.close();
        QMessageBox::information(nullptr, "File loaded", "File loaded successfully.");
    } else {
        QMessageBox::critical(nullptr, "Error", "Could not open the file for reading.");
    }
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
