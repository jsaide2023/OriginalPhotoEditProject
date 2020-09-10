# OriginalPhotoEditProject
C++ Command-Line Photo Editing Program (.ppm)

Description
--------------------------------------------
This C++ program is photo editing program that takes in ppm Files and edits them according to what the user chooses. The user selects from
a main menu that contains choices to manipulate an existing photo or generate random images. If a user chooses to manipulate an existing 
image of their choice, another menu is displayed, which asks them if they want to filter, crop by row or by column as the user specified, 
or rotate their photo by 90 degrees, 180 degrees, or 90 degrees counterclockwise. The photo is edited, then a new file is created. 
After the photo is saved, they are brought back to the manipulate image menu, and they are able to exit that menu by pressing q. If the user wants 
to generate random images, they are prompted with how many images they would like generated. The program will then create the random images, 
save them as ppm files, and create an html file so that the images can be seen through there. After that, the program returns to the main menu. 
If the user would like to quit the whole program, the user must press q in the main menu.

Instructions
--------------------------------------------
Using a Command Line Interface, compile the file by typing g++ -o assg6 assg6.cpp. To run the executable, type ./assg6 .
You could also compile the file as g++ assg6.cpp and run the executable as ./a.out .  

Disclaimer:

If any other data type besides int (integer) is entered, the program will print a message prompting them to enter a valid input. 
However, this causes a infinite loop, and "cin" isn't reached and cannot be used again.  

The file names for the random images are supposed to be named randomly, however the file names may show up twice. 
And, as result, the program will overwrite an existing file with the same name.

If the .ppm file doesn't exist in the same folder as assg6.cpp file itself, an error message will appear and return to the menu.


Author:
--------------------------------------------
-Saide Johnson
 Fall2019
