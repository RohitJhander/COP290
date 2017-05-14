Bubble Screensaver Version 1.0 25-JAN-2015

INTRODUCTION
------------
A cool 2D/3D screensaver animation with some extra features. All the code is written in C++ and used openGL for graphics. For optimization, threads are used, POSIX Threads library in LINUX.

This project was made as an assignment in 'Design and Practices in Computer Science' course under Prof. Huzur Saran and guidance of a TA, Prathmesh Kallurkar, a PhD Scholar.


REQUIREMENT
-----------

Operating System    : Linux
Compiler            : g++
OpenGL Libraries    : freeglut.h glut.h glui.h
Thread Libraries    : pthreads.h

USAGE
-----
Execute             : make execute num_thread=value
Debug               : make debug num_thread=value
Print               : make print num_thread=value

If you change the target, please run $ make clean before

CONFIGURATION
-------------

I. Default Screen Resolution

Change DEFAULT_SCREEN_HEIGHT and DEFUALT_SCREEN_WIDTH in "MyDefines.h"


II. Themes

In "themeFile.txt" following is the protocol for each theme. '#'to declare end.

--------------------------------------
Line# | Value
--------------------------------------
1     | LIGHTING LIGHT0 LIGHT1 LIGHT2
--------------------------------------
2     | Background color float(r,g,b)
--------------------------------------
3,4,5 | LIGHT# Color float(r,g,b)
--------------------------------------
6,7,8 | LIGHT# Position float(r,g,b)
--------------------------------------
9     | <background image file name>


III. Texture Images

These are the file names that should be used to change the textures in the program.

Ball Texture        : "Ball1.bmp"
3D Wall Texture     : "3d.bmp"
3D Background Wall  : "wall.bmp"
2D Background Wall  : <As in themeFile.txt>

***Note that all the images should be in BMP file format***

FILES INCLUDED
--------------
Source Code:

    Ball.cpp          Ball.h          Collision.cpp     Collision.h       GUI.cpp              GUI.h
    imageLoad.cpp     imageLoad.h     MyThread.cpp      MyThread.h        subMenu.cpp          subMenu.h
    Theme.h           themeReader.cpp thr.cpp           thr.h             UtilityFunctions.cpp UtilityFunction.h
    Wall.cpp          Wall.h

Other Sources Files:

    themeFile.txt     img0.bmp        img1.bmp          img2.bmp          wall.bmp             3d.bmp
    ball1.bmp         

Other Files:

    This README.TXT
    Reference Documentations
    Design Document
    CHANGES.TXT
    makefile


TROUBLESHOOTING
---------------

Refer to FAQ.
Any bug? Report us.


FAQ
---

Q. Error like library XYZ not found during compilation?
A. Make sure all the libraries listed are installed on the system. Search for the suitable package for XYZ library.

Q. How can I run this on Windows machine?
A. Use cygwin.

Q. Some file not found error is coming?
A. Texture files might not present in the ./files directory. Refer to CONFIGURATION section.

Q. Error while reading theme?
A. Follow the proper protocol as stated in CONFIGURATION section.


MAINTAINERS
-----------
Patidar, Harishchandra - patidarharish83@gmail.com      - Threads, File Handling
Rohit                  - ricjhander135@gmail.com        - Graphics, Extra Features
Kataria, Manoj         - manoj.mkataria@gmail.com       - Graphics, Physics


BUG REPORTING/SUGGESTIONS
-------------------------
User may report any bug, issues, improvement suggestions to us. Send maintainers email with subject "BUBBLE SCREENSAVER - BUG REPORT"



