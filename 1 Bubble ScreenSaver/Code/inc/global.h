/**
 *@file
 * Useful Structures are defined here.
 */
#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

///To store three dimensional variables like position, velocity, etc.
typedef struct MyStruct{
	float x;
	float y;
	float z;
} ThreeD;

///To store the color attribute in RGB format
typedef struct MyColor{
	float r;
	float g;
	float b;
	MyColor(float x=1.0f , float y=1.0f , float z=1.0f): r(x),g(y),b(z){}	///<Default color : White (1,1,1)
} Color;

#endif
