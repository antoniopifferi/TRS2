How to use in Qt Creator

CMake (recommended)
1) Put CMakeLists.txt at the project root (so paths like src/gui/... are valid).
2) Open Qt Creator → File → Open File or Project... → select CMakeLists.txt.
3) Choose a MSVC x64 Qt 6 kit (Modules require MSVC + CMake >= 3.28).
4) Configure Project → Build.
5) Run.

Notes:
- If your Qt is Qt5, change 'find_package(Qt6 ...)' and 'Qt6::Widgets' to 'Qt5' equivalents.
- If you use MinGW or Clang kits, comment out the C++ modules FILE_SET block.

qmake (.pro) (experimental for C++ modules)
1) Put TRS2.pro at the project root.
2) Open Qt Creator → File → Open File or Project... → select TRS2.pro.
3) Select a MSVC Qt kit.
4) If you hit parallel build issues with module ordering, try building with a single job (e.g. set -j1) or build twice. C++20 modules in qmake are not fully dependency-aware.
