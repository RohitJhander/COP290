#include "Particle.h"
#include <GL/glut.h>
#include "mainw.h"
#include "UtilityFunctions.h"

Particle::Particle(){
	radius = 0.008f;
	reset();
}

void Particle::drawP(){
		glPushMatrix();
		glTranslatef(center.x,center.y,center.z);
		glColor3f(1.0f, 1.0f, 1.0f);
		glutSolidSphere(radius,20,20);
		glPopMatrix();
}

void Particle::moveP(){
	if((center.x < -wall_x.getPosition()) || (center.x >  wall_x.getPosition()) || (center.y < -wall_x.getPosition()) ){
		reset();
	}else{
		center.x = center.x + velocity.x;
		center.y = center.y - velocity.y;
	}
}

ThreeD Particle::getCenter() {
	return center;
}

void Particle::setCenter(float x,float y,float z) {
	center.x = x;
	center.y = y;
	center.z = z;
}

ThreeD Particle::getVelocity() {
	return velocity;
}

void Particle::setVelocity(float vx,float vy,float vz) {
	velocity.x = vx;
	velocity.y = vy;
	velocity.z = vz;
}

void Particle::reset(){
	float temp = 2*getRandomFloat();
	int t = rand()%20;
	if(t < 10){
		temp = -temp;
	}
	center.x = temp*wall_x.getPosition();
	center.y = wall_y.getPosition();
	velocity.x = temp*0.03;
	velocity.y = getRandomFloat()*0.05;
}



