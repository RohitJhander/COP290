/**
 * @file
 * Functions required from main function and other classes.
 * To add extra features/functionality define in this file only.
 */

#ifndef UTILITY_FUNC_H_INCLUDED
#define UTILITY_FUNC_H_INCLUDED

#include "Ball.h"
#include "Theme.h"

extern void preProcessTheme();
extern void setTheme(Theme&);
extern pair<float,float> convPixel(int, int);
extern void changeVelocity(Ball& , float);
extern int findClickedBall(float, float);
extern Ball* createNewBall();
extern void splitBall(Ball& , int);
extern void addBall();
extern void deleteBall(int);
extern void setSpeedText(Ball &);
extern void resetSpeedText();
extern void addNewThread();
extern void addWorkItems();
extern float getRandomFloat();

#endif