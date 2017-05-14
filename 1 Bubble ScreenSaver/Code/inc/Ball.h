/**
 * \class Ball
 */

#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <utility>
#include <math.h>
#include <pthread.h>
#include "global.h"
using namespace std;

///Simple class for defining ball objects.
class Ball {
	private:
		float radius;				///<radius of ball
		ThreeD center,velocity;		///<center and velocity of ball in space
		float speed;				///<speed of ball
		Color color;				///<color of ball in (R,G,B) format
		float mass;					///<mass of ball
		int id;						///<ID of ball
		pthread_mutex_t m_var;		///<mutex associated with ball required for synchronization
	
	public:
		///Constructor
		///Creates a Ball with default values of parameters
		Ball();
		
		///Returns the ID
		int getID();
		///Sets the ID
		void setID(int);
		
		///Returns the center
		ThreeD getCenter();
		///Sets the center at (x,y,z) co-ordinates
		void setCenter(float,float,float);
		

		///Returns velocity
		ThreeD getVelocity();
		///Sets velocity vector (vx, vy, vz)
		void setVelocity(float vx,float vy,float vz);
		
		///Returns radius
		float getRadius();
		///Sets radius
		void setRadius(float r);
		
		///Returns Mass
		float getMass();
		///Sets Mass
		void setMass(float);
		
		///Returns Color
		Color getColor();
		///Set Color
		void setColor(float,float,float);
		
		///Draws the Ball
		void Draw(int num_segments);
		
		///changes the position of ball according to its velocity in a small interval dt
		void Move(float);
		
		///checks if the ball has been clicked
		bool clickListen(float, float);
		
		///Returns mutex for synchronization
		pthread_mutex_t& getMutex();

		///Returns speed of the ball
		float getSpeed();
};

#endif

