#include <GL/glut.h>
#include <math.h>
#include <utility>
#include <ctime>
#include <stdlib.h>
#include "Ball.h"
#include "mainw.h"
#include "UtilityFunctions.h"
#include "MyEnums.h"
using namespace std;


//default parameters
const float VEL_X = 0.05f;
const float VEL_Y = 0.05f;
const float VEL_Z = 0.00f;
const float CENTER_X = 0.0f;
const float CENTER_Y = 0.0f;
const float CENTER_Z = 0.0f;
const float RADIUS = 0.4f;
const float MAX_SPEED = 0.9f;

//constructor
Ball::Ball() {
	velocity.x = VEL_X;
	velocity.y = VEL_Y;
	velocity.z = VEL_Z;
	center.x = CENTER_X;
	center.y = CENTER_Y;
	center.z = CENTER_Z;
	color.r = getRandomFloat();
	color.g = getRandomFloat();
	color.b = getRandomFloat();
	radius = RADIUS;
	mass= radius*radius*radius;
	pthread_mutex_init(&m_var, NULL);
}

ThreeD Ball::getCenter() {
	return center;
}

void Ball::setCenter(float x,float y,float z) {
	center.x = x;
	center.y = y;
	center.z = z;
}

ThreeD Ball::getVelocity() {
	return velocity;
}

void Ball::setVelocity(float vx,float vy,float vz) {
	float speed;
	speed = getSpeed();
	if(speed > MAX_SPEED){					//if speed is more than maximum allowable speed then resets the speed in same direction
		float change = (MAX_SPEED/speed);
		vx = vx * change;
		vy = vy * change;
		vz = vz * change;
	}
	velocity.x = vx;
	velocity.y = vy;
	velocity.z = vz;
}

float Ball::getRadius() {
	return radius;
}

void Ball::setRadius(float r) {
	radius = r;
}

float Ball::getMass() {
	return mass;
}

void Ball::setMass(float mass){
	this->mass = mass;
}

void Ball::Draw(int num_segments) {
	if(enable3D == YES){
		glPushMatrix();
		glTranslatef(center.x,center.y,center.z);
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,t1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glRotatef(rotate,1.0f,1.0f,1.0f);
		
		rotate = rotate + 0.15f;
		if(rotate > 360.0f){
			rotate -= 360.0f;
		}

		gluQuadricTexture(quad,1);
		glColor3f(1.0f, 1.0f, 1.0f);
		gluSphere(quad,radius,20,20);
		
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}else{
		glPushMatrix();
		glTranslatef(center.x,center.y,center.z);
		glColor3f(color.r,color.g,color.b);
		glutSolidSphere(radius,100,100);
		glPopMatrix();
	}
}

void Ball::Move(float dt){
	center.x = center.x + velocity.x * dt;
	center.y = center.y + velocity.y * dt;
	center.z = center.z + velocity.z * dt;
}

int Ball::getID(){
	return id;
}

void Ball::setID(int id){
	this->id = id;
}

bool Ball::clickListen(float x, float y) {
	return pow((center.x-x),2)+pow(center.y-y,2)<= pow(radius,2);
}

pthread_mutex_t& Ball::getMutex(){
	return m_var;
}

float Ball::getSpeed(){
	return sqrt(pow(velocity.x,2) + pow(velocity.y,2) + pow(velocity.z,2));
}

void Ball::setColor(float r, float g, float b){
	color.r = r;
	color.g = g;
	color.b = b;
}

Color Ball::getColor(){
	return color;
}
