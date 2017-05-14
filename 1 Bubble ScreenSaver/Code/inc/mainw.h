/** @file
 * File containing global variables to be used in other files/classes \n
 */

#ifndef Main_H_INCLUDED
#define Main_H_INCLUDED

#include <GL/glut.h>
#include <GL/glui.h>
#include <queue>
#include <vector>
#include <utility>

#include "Ball.h"
#include "MyThread.h"
#include "Wall.h"
#include "Theme.h"
#include "imageLoad.h"
#include "Particle.h"

extern float ALPHA;
extern float rotate;
extern int number_of_balls;
extern vector<MyThread*> threads;
extern float wideAngle;
extern float ratio;
extern int window_height;
extern int window_width;
extern float angleX, angleY, angleZ;
extern int borderNumber;
extern float viewDistance;
extern GLuint t1;
extern GLuint tex3d;
extern GLuint wall_tex;
extern GLUquadric *quad;
extern GLuint _textureId;
extern vector<Theme *> themes;
extern Theme* curTheme;
extern Wall wall_x,wall_y,wall_z;
extern Particle *particles;

#endif
