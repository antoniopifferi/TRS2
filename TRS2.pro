TEMPLATE = app
TARGET = TRS2

QT += widgets
CONFIG += qt warn_on

# C++23 setup
win32:msvc: CONFIG += c++latest      # maps to /std:c++latest
!msvc: QMAKE_CXXFLAGS += -std=c++23  # GCC/Clang

# Treat .ixx files as C++ sources (MSVC will compile them as C++20 modules)
QMAKE_EXT_CPP += ixx

SOURCES += \
    src/gui/main.cpp \
    src/gui/trs2.cpp \
    src/run/runKernel.cpp \
    src/gen/Globals.cpp \
    src/gen/Const.ixx \
    src/gen/Globals.ixx \
    src/step/ArdStep.ixx \
    src/step/MicroStep.ixx \
    src/step/Step.ixx \
    src/step/StepFactory.ixx \
    src/step/TestStep.ixx \
    src/spc/Spc.ixx \
    src/spc/SpcFactory.ixx \
    src/spc/TestSpc.ixx

HEADERS += \
    src/gui/AppLogger.h \
    src/gui/trs2.h \
    src/gui/Binder.h \
    src/run/runKernel.h

FORMS += \
    src/gui/trs2.ui

# Windows GUI subsystem
win32:CONFIG += windows
