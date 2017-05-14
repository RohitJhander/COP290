/**
 * \class MyThread
 * Extends Thread Class publicly
 */
#ifndef MyThread_H_INCLUDED
#define MyThread_H_INCLUDED

#include <pthread.h>
#include <queue>
#include "thr.h"
#include "Ball.h"

///Extends the functionality of Class Thread
class MyThread : public Thread
{
	private:
		queue<Ball*>* q;
		Ball *b;
    public:
    	///Constructor
		MyThread(queue<Ball* >*);
		///sets queue
		void setQueue(queue<Ball*> *);
		///return queue
		queue<Ball*> * getQueue();
		///sets the ball
		void setBall(Ball*);
		///return the ball
		Ball* getBall();
		///function which runs when start() method of parent thread is called
		void* run();
};

#endif
