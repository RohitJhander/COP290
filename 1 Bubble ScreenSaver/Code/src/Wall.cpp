#include "Wall.h"

///Default plane parallel to YZ plane at x=0
Wall::Wall(){
	Wall(YZ,0.0);
}

Wall::Wall(PlaneType plane , float position){
	this->plane = plane;
	this->position = position;
}

PlaneType Wall::getPlane() const{
	return this->plane;
}

float Wall::getPosition() const{
	return this->position;
}

void Wall::setPosition(float pos){
	this->position = pos;
}
