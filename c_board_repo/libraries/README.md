# \*\*New Include Method\*\*

After the migration to GitHub and the syncing of libraries and versions across projects a new way of including the general use libraries is needed. This is due to the library files all always being built if not stopped by preprocessor directive.\*\***THIS ONLY APPLIES TO THE GENERAL USE LIBRARIES FOUND IN /libraries\*\***. Personal libraries in individual projects are unaffected.



### To include a general purpose library

1. Navigate to the /* USER CODE BEGIN Includes */ section of your main.h file. (MAKE SURE YOU ARE IN YOUR .h FILE FOR LIBRARY INCLUDING)
2. Write the following:

 	#define INCLUDE_LIB_NAME

 	#include "LIB_Name.h"

 

   where LIB_NAME is the name of the library in all caps. For example:

 	#define INCLUDE_CAN_RMMOTORS

 	#include "CAN_RMMotors.h"



### Linking a new project

After creating a new project that requires access to our libraries do the following:



1. Right click on the project in your Project explorer bar
2. Go to properties
3. Click the dropdown arrow next to "C/C++ General"
4. Click on "Paths and Symbols"
5. In the "includes" tab add "${WorkspaceDirPath}/c_board_repo/libraries/inc" to both GNU C and Assembly languages
6. Now in the "Source Location" tab click "Link Folder", select "Link to folder in the file system" and either enter "WORKSPACE_LOC/c_board_repo/libraries" or find the libraries folder by clicking on "Variables", selecting "WORKSPACE_LOC" and clicking the "Extend..." button
7. 

