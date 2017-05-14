/**
 * \class Particle
 */

#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include "global.h"

///snow particles in background.
class Particle{
	private:
		float radius;				///<radius of snow particles
		ThreeD center;		///<center of snow particles
		ThreeD velocity;	///<velocity of snow particles	
	public:
		///Constructor
		Particle();

		///returns radius
		float getRadius();
		///sets the radius
		void setRadius(float r);

		///returns center
		ThreeD getCenter();
		///sets center
		void setCenter(float,float,float);
		
		///returns velocity
		ThreeD getVelocity();
		///sets velocity
		void setVelocity(float,float,float);

		///drawing utility function
		void drawP();
		///changes the position of snow particle
		void moveP();

		///resets the position of snow particle
		void reset();
};

#endif
