#include "MyThread.h"
#include "Collision.h"
#include "mainw.h"

MyThread::MyThread(queue<Ball*>* myqueue) : q(myqueue) {}


void* MyThread::run() {
	Ball* workitem;
	
	check_Collision_With_Wall(*b,wall_x);
	check_Collision_With_Wall(*b,wall_y);
	check_Collision_With_Wall(*b,wall_z);
	
	int n = q->size();
	while(n--){
		workitem = q->front();
		q->pop();
		check_Collision_With_Ball(*b,*workitem);
	}
	return NULL;
}

void MyThread::setQueue(queue<Ball* > *q){
	this->q = q;
}

queue<Ball* >* MyThread::getQueue(){
	return q;
}

void MyThread::setBall(Ball* b){
	this->b = b;
}

Ball* MyThread::getBall(){
	return b;
}