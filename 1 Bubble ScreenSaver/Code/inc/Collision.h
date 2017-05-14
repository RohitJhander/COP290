/**
 * @file
 * Functions for maintaining the physics of the system. \n
 * All the collisions are elastic.
 */
#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "Wall.h"
#include "Ball.h"

///Checks for a possible collision of a ball with a wall and accordingly update the velocity
void check_Collision_With_Wall(Ball & , Wall &);
///Checks for a possible collision of two balls with each other and accordingly update the velocities of both the balls using their respective mutexes
void check_Collision_With_Ball(Ball & , Ball &);

#endif
