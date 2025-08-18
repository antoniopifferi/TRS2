- P ParmS (ParmS.h): only parameters derived from UIR - Immutable at run time
- class Step (Step.h): all general variables and function needed during operation 
- Device: implementation of a class. Use a constructor (e.g. createStep) to generate a new object. The problem is that you cannot use the default new since the type is different. mYou first create with step=createStepDev nd then assign the variables to the generic step ovject
- New object in UI:
	o create the object in the GUI
	o add in Parm
	o add in Table
	o add the variables in the Class definition
	o copy in the generic Class

DEFINITION AND DECLARATIONS:
- Declaration: the type of a variable, function, or class is defined. This tells the compiler what to expect but does not allocate memory.
- Definition: the actual implementation of a variable, function, or class. This allocates memory and provides the necessary code for execution.
- Assignment: the process of giving a value to a variable or object after it has been defined. This is done using the assignment operator (`=`) and does not change the type or structure of the variable or object.

MODULE INTERFACES:
- use a single file for definitions and declarations
- Must use C++20 or later
- #include: can be used for legacy code, but must stay at the top of the file after the module declaration and before export module

GLOBAL VARIABLES:
- you can declare global variables in .ixx, but you cannot define them there. The definition must be in a .cpp file with the same name as the module.
- you must use `export` to make the global variable available outside the module.

QT AND C++20 MODULES:
- for the time being, better using old .h .cpp files in GUI

FILE DIRECTORY STRUCTURE:
- src: contains all source files
- lib: contains all libraries
- bin: contains all executable files
- tests: contains all test files
- docs: contains all documentation files
- examples: contains example files
- build: contains build files and configurations
- dist: contains distribution files and packages
- logs: contains log files generated during the execution of the application

CHANGING FILE DIRECTORY STRUCTURE:
- remember to delete or exclude the old files from the project
- if problems, you have to edit the .vcxproj and remove all old directories/includes with wrong names
- Show the real error inputs: Build → Build with MSBuild output set to Detailed (Tools → Options → Projects and Solutions → Build and Run → MSBuild project build output verbosity: Detailed). Look at the compiler command line for /I ... entries pointing to old paths.

USE OF FORMAT IN C++20 MODULES:
- Format is not supported in C++20 modules. You can use the `std::format` library, but it requires C++20 support and may not be available in all compilers. If you need to format strings, consider using `std::ostringstream` or other string manipulation techniques instead.
- outText(std::format("Stepper {} ({}) moved to position = {}", this->iS, P.Step[this->iS].Type, this->actual));
