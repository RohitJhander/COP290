/**
 * \class Wall
 */

#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

enum PlaneType {XY,XZ,YZ};

///Wall object to define boundaries of window/box.
class Wall{
	private:
		PlaneType plane;	///<Type of plane
		float position;
	public:
		///Constructor
		Wall();
		///Creates wall with at given positon of given type
		Wall(PlaneType,float);
		///Returns type of the plane
		PlaneType getPlane() const;
		///Returns the position of the plane
		float getPosition() const;
		///Sets the position of the plane
		void setPosition(float);
};

#endif
