#include "Collision.h"
#include <iostream>
#include <cmath>
using namespace std;

void check_Collision_With_Wall(Ball &ball , Wall & wall){
	
	pthread_mutex_lock(&ball.getMutex());
	float c_x = ball.getCenter().x;
	float c_y = ball.getCenter().y;
	float c_z = ball.getCenter().z;
	float v_x = ball.getVelocity().x;
	float v_y = ball.getVelocity().y;
	float v_z = ball.getVelocity().z;
	float r = ball.getRadius();
	pthread_mutex_unlock(&ball.getMutex());
	ThreeD toReturn;
	
	toReturn.x = v_x ;
	toReturn.y = v_y ;
	toReturn.z = v_z ;
	
	PlaneType plane = wall.getPlane();
	float pos = wall.getPosition();
	
	switch(plane){
		case XY:
				if(c_z+r > pos){
					toReturn.z = (v_z>0 ? -v_z : v_z);
				}
				if(c_z-r < -pos){
					toReturn.z = (v_z<0 ? -v_z : v_z);
				}
				break;
		case XZ:
				if(c_y+r > pos){
					toReturn.y = (v_y>0 ? -v_y : v_y);
				}
				if(c_y-r < -pos){
					toReturn.y = (v_y<0 ? -v_y : v_y);
				}
				break;
		case YZ:
				if(c_x+r > pos){
					toReturn.x = (v_x>0 ? -v_x : v_x);
				}
				if(c_x-r < -pos){
					toReturn.x = (v_x<0 ? -v_x : v_x);
				}
				break;
		default:
				break;
	}
	pthread_mutex_lock(&ball.getMutex());
	ball.setVelocity(toReturn.x,toReturn.y,toReturn.z);
	pthread_mutex_unlock(&ball.getMutex());
}

void check_Collision_With_Ball(Ball &b1, Ball &b2) {
	
	pthread_mutex_lock(&b1.getMutex());
	float x1=b1.getCenter().x , y1=b1.getCenter().y , z1=b1.getCenter().z;
	float u1_x=b1.getVelocity().x , u1_y=b1.getVelocity().y , u1_z=b1.getVelocity().z;
	float m1=b1.getMass();
	pthread_mutex_unlock(&b1.getMutex());
	
	pthread_mutex_lock(&b2.getMutex());
	float x2=b2.getCenter().x , y2=b2.getCenter().y , z2=b2.getCenter().z;
	float u2_x=b2.getVelocity().x , u2_y=b2.getVelocity().y , u2_z=b2.getVelocity().z;
	float m2=b2.getMass();
	pthread_mutex_unlock(&b2.getMutex()); 
	
	float x = x2-x1, y = y2-y1, z = z2-z1;	
	float dist = (x*x) + (y*y) + (z*z);		//square of distance between centers
	float v1_n,v2_n;				//velocities along normal direction
	
	v1_n = (u1_x*x+u1_y*y+u1_z*z);
	v2_n = (u2_x*x+u2_y*y+u2_z*z);
	
	ThreeD v1,v2;
	
	v1.x = u1_x;
	v1.y = u1_y;
	v1.z = u1_z;
	v2.x = u2_x;
	v2.y = u2_y;
	v2.z = u2_z;
	
	if (dist <= pow(b1.getRadius()+b2.getRadius(),2) && (v1_n-v2_n)>0) {
		
		v1.x = ( ((u1_x*dist)-(x*v1_n)) + (x*((m1-m2)*(v1_n)+2*m2*(v2_n)))/(m1+m2) ) / (dist);
		v1.y = ( ((u1_y*dist)-(y*v1_n)) + (y*((m1-m2)*(v1_n)+2*m2*(v2_n)))/(m1+m2) ) / (dist);
		v1.z = ( ((u1_z*dist)-(z*v1_n)) + (z*((m1-m2)*(v1_n)+2*m2*(v2_n)))/(m1+m2) ) / (dist);
		
		x = -x; y = -y; z = -z;
		v1_n = -v1_n;
		v2_n = -v2_n;
		
		v2.x = ( ((u2_x*dist)-(x*v2_n)) + (x*((m2-m1)*(v2_n)+2*m1*(v1_n)))/(m1+m2) ) / (dist);
		v2.y = ( ((u2_y*dist)-(y*v2_n)) + (y*((m2-m1)*(v2_n)+2*m1*(v1_n)))/(m1+m2) ) / (dist);
		v2.z = ( ((u2_z*dist)-(z*v2_n)) + (z*((m2-m1)*(v2_n)+2*m1*(v1_n)))/(m1+m2) ) / (dist);
		
		pthread_mutex_lock(&b1.getMutex());
		b1.setVelocity(v1.x,v1.y,v1.z);
		pthread_mutex_unlock(&b1.getMutex());
		
		pthread_mutex_lock(&b2.getMutex());
		b2.setVelocity(v2.x,v2.y,v2.z);
		pthread_mutex_unlock(&b2.getMutex());		
	}	
}
