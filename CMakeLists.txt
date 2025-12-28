# Using Qt6 6.10.1
cmake_minimum_required(VERSION 3.28)
project(TRS2 LANGUAGES CXX)

# --- C++ standard ---
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Modules: ON globally (your requirement) ---
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
list(APPEND CMAKE_TRY_COMPILE_PLATFORM_VARIABLES CMAKE_CXX_SCAN_FOR_MODULES)

# --- Qt integrations ---
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Workaround: dependency probes (try_compile) don't need modules; disable briefly.
set(_save_scan ${CMAKE_CXX_SCAN_FOR_MODULES})
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets PrintSupport SerialPort)
set(CMAKE_CXX_SCAN_FOR_MODULES ${_save_scan})

# ---- Executable ----
qt_add_executable(TRS2 MANUAL_FINALIZATION
  # Ordinary sources
  src/gui/main.cpp
  src/gui/trs2.cpp
  src/run/runKernel.cpp
  lib/qcustomplot.cpp

  # headers/ui that need moc/uic:
  src/gui/Binder.h
  src/gui/AppLogger.h
  src/run/runKernel.h
  src/gui/trs2.ui
)

# Enable module scanning explicitly for this target
set_property(TARGET TRS2 PROPERTY CXX_SCAN_FOR_MODULES ON)

# Module interface units
target_sources(TRS2 PRIVATE
  FILE_SET cxx_modules TYPE CXX_MODULES FILES
    src/gen/Const.ixx
    src/gen/Globals.ixx
    src/gen/Data.ixx
    src/spc/Spc.ixx
    src/spc/SpcFactory.ixx
    src/spc/TestSpc.ixx
    src/spc/SpcMharp.ixx
    src/step/Step.ixx
    src/step/StepFactory.ixx
    src/step/StepArd.ixx
    src/step/StepMicro.ixx
    src/step/StepPi.ixx
    src/step/StepTest.ixx
)

# Finalize target (Qt Creator integration / deployment helpers)
qt_finalize_executable(TRS2)

# Link Qt
target_link_libraries(TRS2 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::PrintSupport Qt6::SerialPort)

# Link vendor libraries from lib folder
# MultiHarp (64-bit)
target_link_libraries(TRS2 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/mhlib64.lib")
# PI GCS2 DLL import library (64-bit)
target_link_libraries(TRS2 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/PI_GCS2_DLL_x64.lib")

# MSVC: treat sources as UTF-8
if (MSVC)
  target_compile_options(TRS2 PRIVATE /utf-8)
endif()

# Include dirs
target_include_directories(TRS2 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/lib"
)

# Keep AUTOMOC away from module interface units
set_source_files_properties(
  src/gen/Const.ixx
  src/gen/Globals.ixx
  src/gen/Data.ixx
  src/spc/Spc.ixx
  src/spc/SpcFactory.ixx
  src/spc/TestSpc.ixx
  src/spc/SpcMharp.ixx
  src/step/Step.ixx
  src/step/StepFactory.ixx
  src/step/StepArd.ixx
  src/step/StepMicro.ixx
  src/step/StepPi.ixx
  src/step/StepTest.ixx
  PROPERTIES SKIP_AUTOMOC ON
)

# Windows-only settings
if (WIN32)
  set_property(TARGET TRS2 PROPERTY WIN32_EXECUTABLE TRUE)
  target_compile_definitions(TRS2 PRIVATE
    UNICODE _UNICODE WIN32 _WINDOWS _ENABLE_EXTENDED_ALIGNED_STORAGE
    $<$<CONFIG:Release>:NDEBUG;QT_NO_DEBUG>
  )
else()
  target_compile_definitions(TRS2 PRIVATE
    $<$<CONFIG:Release>:NDEBUG;QT_NO_DEBUG>
  )
endif()

# AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${CMAKE_CURRENT_SOURCE_DIR}/ui"
)
