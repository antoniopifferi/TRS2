#changed Qt6 6.9
cmake_minimum_required(VERSION 3.28)
project(TRS2 LANGUAGES CXX)

# --- C++ standard ---
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Modules: ON globally (your requirement) ---
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# Make sure try_compile child projects know about this variable
list(APPEND CMAKE_TRY_COMPILE_PLATFORM_VARIABLES CMAKE_CXX_SCAN_FOR_MODULES)

# --- Qt integrations ---
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Workaround: dependency probes (try_compile) don't need modules; disable briefly.
set(_save_scan ${CMAKE_CXX_SCAN_FOR_MODULES})
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets PrintSupport)
# (If you add other find_package(...) calls, keep them inside this OFF section.)
set(CMAKE_CXX_SCAN_FOR_MODULES ${_save_scan})

# ---- Executable ----
qt_add_executable(TRS2
  # Module interface units (.ixx)
  src/gen/Const.ixx
  src/gen/Globals.ixx
  src/spc/Spc.ixx
  src/spc/SpcFactory.ixx
  src/spc/TestSpc.ixx
  src/step/ArdStep.ixx
  src/step/MicroStep.ixx
  src/step/Step.ixx
  src/step/StepFactory.ixx
  src/step/TestStep.ixx

  # Ordinary sources
  #src/gen/Globals.cpp
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

# Enable module scanning explicitly for this target (belt & suspenders)
set_property(TARGET TRS2 PROPERTY CXX_SCAN_FOR_MODULES ON)

# Help CMake with BMI ordering by explicitly marking module files
target_sources(TRS2 PRIVATE
  FILE_SET cxx_modules TYPE CXX_MODULES FILES
    src/gen/Const.ixx
    src/gen/Globals.ixx
    src/spc/Spc.ixx
    src/spc/SpcFactory.ixx
    src/spc/TestSpc.ixx
    src/step/ArdStep.ixx
    src/step/MicroStep.ixx
    src/step/Step.ixx
    src/step/StepFactory.ixx
    src/step/TestStep.ixx
)

target_link_libraries(TRS2 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::PrintSupport)


target_include_directories(TRS2 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lib    
)



# Keep AUTOMOC away from module interface units
set_source_files_properties(
  src/gen/Const.ixx
  src/gen/Globals.ixx
  src/spc/Spc.ixx
  src/spc/SpcFactory.ixx
  src/spc/TestSpc.ixx
  src/step/ArdStep.ixx
  src/step/MicroStep.ixx
  src/step/Step.ixx
  src/step/StepFactory.ixx
  src/step/TestStep.ixx
  PROPERTIES SKIP_AUTOMOC ON
)

# Windows-only settings
if (WIN32)
  set_property(TARGET TRS2 PROPERTY WIN32_EXECUTABLE TRUE)
  target_compile_definitions(TRS2 PRIVATE
    UNICODE _UNICODE WIN32 _WINDOWS _ENABLE_EXTENDED_ALIGNED_STORAGE
    $<$<CONFIG:Release>:NDEBUG;QT_NO_DEBUG>
  )
  # Copy Qt DLLs after each build (Debug/Release)
  set(QT_ROOT "C:/Qt/6.9.2/msvc2022_64")
  add_custom_command(TARGET TRS2 POST_BUILD
    COMMAND "${QT_ROOT}/bin/windeployqt.exe"
            --compiler-runtime
            --no-translations
            --dir "$<TARGET_FILE_DIR:TRS2>"
            "$<TARGET_FILE:TRS2>"
    VERBATIM
  )
else()
  # Non-Windows: only keep non-Windows defines
  target_compile_definitions(TRS2 PRIVATE
    $<$<CONFIG:Release>:NDEBUG;QT_NO_DEBUG>
  )
endif()

# Help AUTOUIC if .ui files are nested
set(CMAKE_AUTOUIC_SEARCH_PATHS
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

