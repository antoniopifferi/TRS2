QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DevSource/MicroStep.cpp \
    GenSource/Parm.cpp \
    GenSource/Step.cpp \
    GenSource/runKernel.cpp \
    GuiSource/main.cpp \
    GuiSource/trs2.cpp

HEADERS += \
    DevSource/MicroStep.h \
    GenSource/Const.h \
    GenSource/Parm.h \
    GenSource/Step.h \
    GenSource/runKernel.h \
    GuiSource/trs2.h

FORMS += \
    GuiSource/trs2.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
