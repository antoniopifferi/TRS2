#include "Gui.h"
//#include "./ui_test5.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Test5::Test5(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::Test5)
{
    ui->setupUi(this);

    // Create Table
    for(int is=0;is<2;is++){
        addTab("String", is, &P.vString[is]);
        addTab("Int", is, &P.vInt[is]);
        addTab("Double", is, &P.vDouble[is]);
        addTab("Combo", is, &P.vCombo[is]);
        addTab("Check", is, &P.vCheck[is]);
    }

    // Complete Table
    for (auto& iT : T) {
        QObject* obj = findChild<QObject*>(iT.Name);
        if (obj) {
            const QMetaObject* meta = obj->metaObject();
            iT.Type = meta->className();
        }
    }

    // Connect Signals
    for (const auto& iT : T) {
        QObject* obj = findChild<QObject*>(iT.Name);
        if (obj) {
            if (iT.Type == "QLineEdit") {
                connect(obj, SIGNAL(editingFinished()), this, SLOT(updateTFromUI()));
            } else if (iT.Type == "QSpinBox"){
                connect(obj, SIGNAL(valueChanged(int)), this, SLOT(updateTFromUI()));
            } else if (iT.Type == "QDoubleSpinBox") {
                connect(obj, SIGNAL(valueChanged(double)), this, SLOT(updateTFromUI()));
            } else if (iT.Type == "QComboBox") {
                connect(obj, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTFromUI()));
            } else if (iT.Type == "QCheckBox") {
                connect(obj, SIGNAL(clicked()), this, SLOT(updateTFromUI()));
            }
        }
    }

    // LOAD SETTINGS
    loadSet("c:\\Temp\\TRS.TRS");
}

Test5::~Test5()
{
    saveSet("c:\\Temp\\TRS.TRS");
    delete ui;
}

void Test5::updateTFromUI() {
    for (const auto& iT : T) {
        QObject* obj = findChild<QObject*>(iT.Name);
        if (obj && obj == sender()) {
            if (iT.Type == "QLineEdit") {
                *static_cast<QString*>(iT.Var) = qobject_cast<QLineEdit*>(obj)->text();
            } else if (iT.Type == "QSpinBox") {
                *static_cast<int*>(iT.Var) = qobject_cast<QSpinBox*>(obj)->value();
            } else if (iT.Type == "QDoubleSpinBox") {
                *static_cast<double*>(iT.Var) = qobject_cast<QDoubleSpinBox*>(obj)->value();
            } else if (iT.Type == "QComboBox") {
                *static_cast<QString*>(iT.Var) = qobject_cast<QComboBox*>(obj)->currentText();
            } else if (iT.Type == "QCheckBox") {
                *static_cast<bool*>(iT.Var) = qobject_cast<QCheckBox*>(obj)->isChecked();
            }
            break;
        }
    }
    printP();
}

void Test5::printP() {
    qDebug() << "vInt:" << P.vInt[1];
    qDebug() << "vDouble:" << P.vDouble[1];
    qDebug() << "vString:" << P.vString[1];
    qDebug() << "vCombo:" << P.vCombo[1];
    qDebug() << "vCheck:" << P.vCheck[1];
}

void Test5::addTab(QString Prefix, int Id, void* Var) {
    QString Name;
    if(Id==-1) // just single element
        Name=Prefix;
    else
        Name=Prefix+"_"+QString::number(Id+1);

    QObject* obj = findChild<QObject*>(Name);
    const QMetaObject* meta = obj->metaObject();
    QString Type = meta->className();

    T.push_back({Name,Type,Var});
}

void Test5::saveSet(QString FilePath){
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

void Test5::loadSet(QString FilePath) {
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
