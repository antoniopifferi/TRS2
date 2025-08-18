cmake_minimum_required(VERSION 3.29)
# Generated from TRS2 Visual Studio project by ChatGPT on 2025-08-18
project(TRS2 LANGUAGES CXX)

# ---- C++ standard ----
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Qt helpers ----
# These let CMake automatically run moc/uic/rcc when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ---- C++20 modules (MSVC / CMake 3.29+) ----
# These enable dependency scanning for .ixx files.
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# ---- Find Qt 6 ----
# Adjust components as needed (e.g., add Network, Svg, etc.).
find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Widgets)

# ---- Sources ----
# List discovered from TRS2.vcxproj.filters
set(SRCS
  src/gui/main.cpp
  src/gui/trs2.cpp
  src/gen/Globals.cpp
  src/run/runKernel.cpp
)

# Headers that require moc (contain Q_OBJECT)
set(MOC_HEADERS
  src/gui/AppLogger.h
  src/gui/trs2.h
)

# Regular headers (for IDE/source groups; not strictly needed to build)
set(HDRS
  src/gui/Binder.h
  src/run/runKernel.h
)

# Qt Designer UI files
set(UIS
  src/gui/trs2.ui
)

# C++20 module interface units (.ixx)
# If your modules import each other, order does not matter; CMake scans dependencies.
set(MODULES
  src/gen/Const.ixx
  src/gen/Globals.ixx
  src/step/ArdStep.ixx
  src/step/MicroStep.ixx
  src/step/Step.ixx
  src/step/StepFactory.ixx
  src/step/TestStep.ixx
)

# ---- Target ----
qt_add_executable(TRS2
  MANUAL_FINALIZATION
  ${SRCS}
  ${MOC_HEADERS}
  ${HDRS}
  ${UIS}
)

# Add C++ module interface files
# On MSVC/Clang with CMake 3.29+, this will compile modules correctly.
target_sources(TRS2
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES
    BASE_DIRS
      ${CMAKE_CURRENT_LIST_DIR}/src
    FILES
      ${MODULES}
)

# Include dirs (add more as needed)
target_include_directories(TRS2 PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src
)

# Link Qt libraries
target_link_libraries(TRS2 PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)

# Warnings (tweak to taste)
if (MSVC)
  target_compile_options(TRS2 PRIVATE /W4 /permissive- /Zc:__cplusplus /utf-8)
else()
  target_compile_options(TRS2 PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Treat source tree layout as VS "filters"
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES
  ${SRCS} ${HDRS} ${MOC_HEADERS} ${UIS} ${MODULES}
)

# Windows GUI subsystem (uncomment to hide the console on Windows)
# if (WIN32)
#   set_target_properties(TRS2 PROPERTIES WIN32_EXECUTABLE TRUE)
# endif()

# Post-build deployment helper for Qt on Windows (optional)
if (WIN32)
  add_custom_command(TARGET TRS2 POST_BUILD
    COMMAND "${Qt6_DIR}/../../../bin/windeployqt.exe" "$<TARGET_FILE:TRS2>"
    VERBATIM
  )
endif()

qt_finalize_executable(TRS2)

# ---- Install rules (optional) ----
install(TARGETS TRS2 RUNTIME DESTINATION .)
