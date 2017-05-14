/**
 * @file
 * openGL functions are maintained in this seperate file. \n
 * Any changes regarding graphics rendering should be made here.
 */

#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <GL/glut.h>
#include <GL/glui.h>

#include "imageLoad.h"

///glutMouseFunc
extern void handleMouse(int, int, int, int);
///glutReshapeFunc
extern void handleResize(int, int);
///glutKeyboardFunc
extern void handleKeypress(unsigned char,int, int);
///loads texture from an Image
extern GLuint loadTexture(Image*);
///draws a 3D box at boundaries of balls i.e. walls
extern void drawBox();
///glutDrawFunc
extern void drawScene();
///initialize the graphics rendering
extern void initRendering();
///glutTimerFunc
extern void update(int);
#endif