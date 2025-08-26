QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++23

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/gen/Globals.cpp \
    src/gui/main.cpp \
    src/gui/trs2.cpp \
    src/run/runKernel.cpp

HEADERS += \
    src/gen/Globals.ixx \
    src/gui/AppLogger.h \
    src/gui/Binder.h \
    src/gui/trs2.h \
    src/gui/ui_trs2.h \
    src/run/runKernel.h \
    src/spc/Spc.ixx \
    src/spc/SpcFactory.ixx \
    src/spc/TestSpc.ixx \
    src/step/ArdStep.ixx \
    src/step/Step.ixx \
    src/step/StepFactory.ixx \
    src/step/TestStep.ixx

FORMS += \
    src/gui/trs2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/gen/Const.ixx \
    src/gen/Data.ixx \
    src/step/MicroStep.ixx
