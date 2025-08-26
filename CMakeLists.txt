cmake_minimum_required(VERSION 3.28)

project(TRS2 VERSION 0.1 LANGUAGES CXX)

# C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Qt automoc/uic/rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# MSVC niceties
if (MSVC)
  add_compile_options(/permissive- /Zc:__cplusplus)
endif()

# ---- Qt ----
find_package(Qt6 6.5 REQUIRED COMPONENTS Widgets)

qt_add_executable(TRS2
    src/gui/main.cpp
    src/gui/trs2.cpp
    src/run/runKernel.cpp
    src/gen/Globals.cpp

    # UI
    src/gui/trs2.ui

    # Headers that likely need MOC (AUTOMOC will pick up Q_OBJECT)
    src/gui/AppLogger.h
    src/gui/trs2.h
    # Other headers (optional to list for IDE grouping)
    src/gui/Binder.h
    src/run/runKernel.h
)

target_link_libraries(TRS2 PRIVATE Qt6::Widgets)

# ----- C++20 Modules (.ixx) -----
# Requires MSVC toolchain and CMake >= 3.28.
# If you use a non-MSVC compiler/kit, comment this block out.
if (MSVC)
  target_sources(TRS2 PRIVATE
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
      src/gen/Const.ixx
      src/gen/Globals.ixx
      src/step/ArdStep.ixx
      src/step/MicroStep.ixx
      src/step/Step.ixx
      src/step/StepFactory.ixx
      src/step/TestStep.ixx
      src/spc/Spc.ixx
      src/spc/SpcFactory.ixx
      src/spc/TestSpc.ixx
  )
endif()

# GUI subsystem on Windows
if (WIN32)
  set_property(TARGET TRS2 PROPERTY WIN32_EXECUTABLE TRUE)
endif()

qt_finalize_executable(TRS2)
