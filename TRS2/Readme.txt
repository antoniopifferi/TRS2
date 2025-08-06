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

GLOBAL VARIABLES:
- you can declare global variables in .ixx, but you cannot define them there. The definition must be in a .cpp file with the same name as the module.
- you must use `export` to make the global variable available outside the module.
