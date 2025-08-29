cmake_minimum_required(VERSION 3.28)
project(TRS2 LANGUAGES CXX)

# C++23 + module scanning
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# Qt integrations
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.9 REQUIRED COMPONENTS Core Gui Widgets PrintSupport)

# ---- Executable ----
qt_add_executable(TRS2
  src/gen/Const.ixx
  src/gen/Globals.cpp
  src/gen/Globals.ixx
  src/gui/main.cpp
  src/gui/trs2.cpp
  src/run/runKernel.cpp
  src/spc/Spc.ixx
  src/spc/SpcFactory.ixx
  src/spc/TestSpc.ixx
  src/step/ArdStep.ixx
  src/step/MicroStep.ixx
  src/step/Step.ixx
  src/step/StepFactory.ixx
  src/step/TestStep.ixx
  lib/qcustomplot.cpp
  # headers/ui that need moc/uic:
  src/gui/Binder.h
  src/gui/AppLogger.h
  src/run/runKernel.h
  src/gui/trs2.ui
)

target_link_libraries(TRS2 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::PrintSupport)

target_include_directories(TRS2 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Windows GUI subsystem (no console)
if (WIN32)
  set_property(TARGET TRS2 PROPERTY WIN32_EXECUTABLE TRUE)
endif()

# Help AUTOUIC if .ui files are nested
set(CMAKE_AUTOUIC_SEARCH_PATHS
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

# Release-only defines (don’t force NDEBUG in Debug)
target_compile_definitions(TRS2 PRIVATE
  UNICODE _UNICODE WIN32 _WINDOWS _ENABLE_EXTENDED_ALIGNED_STORAGE
  $<$<CONFIG:Release>:NDEBUG;QT_NO_DEBUG>
)

if (COMMAND qt_finalize_executable)
  qt_finalize_executable(TRS2)
endif()

# ---- Copy Qt DLLs after each build (Debug/Release) ----
set(QT_ROOT "C:/Qt/6.9.2/msvc2022_64")
add_custom_command(TARGET TRS2 POST_BUILD
  COMMAND "${QT_ROOT}/bin/windeployqt.exe"
          --compiler-runtime
          --no-translations
          --dir "$<TARGET_FILE_DIR:TRS2>"
          "$<TARGET_FILE:TRS2>"
  VERBATIM
)
