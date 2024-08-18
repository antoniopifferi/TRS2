- P ParmS (ParmS.h): only parameters derived from UIR - Immutable at run time
- class Step (Step.h): all general variables and function needed during operation 
- Device: implementation of a class. Use a constructor (e.g. createStep) to generate a new object. The problem is that you cannot use the default new since the type is different. mYou first create with step=createStepDev nd then assign the variables to the generic step ovject
- New object in UI:
	o create the object in the GUI
	o add in Parm
	o add in Table
	o add the variables in the Class definition
	o copy in the generic Class