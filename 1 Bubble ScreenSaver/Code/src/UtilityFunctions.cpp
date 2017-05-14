#include "UtilityFunctions.h"
#include "mainw.h"
#include "subMenu.h"
#include "MyDefines.h"
#include "MyEnums.h"
#include "themeReader.h"
#include "GUI.h"

void preProcessTheme() {	
	string filename = "files/themeFile.txt";
	themes = readThemes(filename.c_str());
	curTheme = themes[0];
}

void setTheme(Theme& theme) {
	curTheme = &theme;
	glClearColor(curTheme->background.r, curTheme->background.g, curTheme->background.b, 0.0f);
	Image* image = loadImage(curTheme->image.c_str());
	_textureId = loadTexture(image);
	delete image;
	if(theme.isLight[0]) {
		glEnable(GL_LIGHTING);
	} else {
		glDisable(GL_LIGHTING);
	}
	if(theme.isLight[1]) {
		glEnable(GL_LIGHT0);
	} else {
		glDisable(GL_LIGHT0);
	}
	if(theme.isLight[2]) {
		glEnable(GL_LIGHT1);
	} else {
		glDisable(GL_LIGHT1);
	}
	if(theme.isLight[3]) {
		glEnable(GL_LIGHT2);
	} else {
		glDisable(GL_LIGHT2);
	}
}

pair<float,float> convPixel(int x, int y) {
	float xf = float(2*x-window_width)*(wall_x.getPosition())/(window_width);
	float yf = float(window_height-2*y)*(wall_y.getPosition())/(window_height);
	return make_pair(xf,yf);
}

void changeVelocity(Ball& b, float factor) {
	b.setVelocity(b.getVelocity().x*factor,b.getVelocity().y*factor, b.getVelocity().z*factor);
}

int findClickedBall(float xf, float yf) {
	int i=0;
	for(;i<threads.size();i++) {
		if(threads[i]->getBall()->clickListen(xf,yf)){
			#ifdef PRINT
				cout<<"Ball with ID = "<<i<<" clicked\n";		
			#endif
			return i;
		}
	}
	return -1;
}

Ball* createNewBall(){
	#ifdef PRINT
		cout<<"createNewBall() function called\n";
	#endif
	Ball *b = new Ball();
	if(b == NULL){
		cout<<"Ball can not be created : insufficient memory\n";
		exit(0);
	}
	float SPEED = b->getSpeed();
	int theta = 45 , offset = 40;
	float extreme_x = wall_x.getPosition();
	float extreme_y = wall_y.getPosition();
	float extreme_z = wall_z.getPosition();
	float default_vel_x = b->getVelocity().x;
	float default_vel_y = b->getVelocity().y;
	float default_vel_z = b->getVelocity().z;
	float r = b->getRadius();
	
	if(number_of_balls > 50){
		r = sqrt(4.5/number_of_balls);
		b->setRadius(r);
	}
	
	int random_num = rand()%4;
	theta = rand()%11 + offset;
	ThreeD v;

	switch(random_num){
		case 0:
				b->setCenter(-extreme_x+r , extreme_y-r , 0.0f);	//	upper-left corner
				v.x = (SPEED * cosf((float)theta));
				v.y = (SPEED * sinf((float)theta));
				break;
		case 1:
				b->setCenter(-extreme_x+r , -extreme_y+r , 0.0f);	//	lower-left corner
				v.x = (SPEED * cosf((float)theta));
				v.y = (-SPEED * sinf((float)theta));
				break;
		case 2:
				b->setCenter(extreme_x-r , extreme_y-r , 0.0f);	//	upper-right corner
				v.x = (-SPEED * cosf((float)theta));
				v.y = (SPEED * sinf((float)theta));
				break;
		case 3:
				b->setCenter(extreme_x-r , -extreme_y+r , 0.0f);	//	lower-right corner
				v.x = (-SPEED * cosf((float)theta));
				v.y = (-SPEED * sinf((float)theta));
				break;
		default: break;
	}
	
	if(enable3D == YES){ 
		v.z = getRandomFloat();
	}else{
		v.z = default_vel_z ;
	}
	if(rand()%20 < 10){
		v.z = -v.z;
	}
	b->setVelocity(v.x,v.y,v.z);
	b->setID(threads.size());
	
	return b;
}

void splitBall(Ball& b, int n) {
	#ifdef PRINT
		cout<<"splitBall() function called on Ball with id = "<<b.getID()<<endl;
		cout<<"Ball to be splitted into "<<n<<" smaller balls\n";
	#endif
	ThreeD center = b.getCenter();
	float speed =  b.getSpeed();
	float radius = b.getRadius()/sqrt(n);
	float omega = atan(b.getVelocity().y/b.getVelocity().x);
	float theta = 2*PI/n;
	int size = threads.size();
	int i;
	for(i=1 ; i<n ; i++){
		addNewThread();
		Ball *temp = threads[size+i-1]->getBall();
		temp->setRadius(radius);
		temp->setMass(radius*radius*radius);
		temp->setCenter(center.x,center.y,center.z);
		temp->setVelocity(speed*cosf(omega+i*theta), speed*sinf(omega+i*theta),0.0f);
	}
	b.setRadius(radius);
	b.setVelocity(speed*cosf(omega), speed*sinf(omega),0.0f);
}

void deleteBall(int id){
	#ifdef PRINT
		cout<<"deleteBall() function called : Initially, threads.size() = "<<threads.size()<<endl;
	#endif
	int size = threads.size();
	if(size == 0)
		return;
	if(id != size-1){
		MyThread* tempthread = threads[id];
		threads[id] = threads[size-1];
		threads[size-1] = tempthread;

		threads[id]->getBall()->setID(id);
	}
	delete threads[size-1];
	threads.erase(threads.begin()+size-1);
	#ifdef PRINT
		cout<<"Thread erased : Finally, threads.size() = "<<threads.size()<<endl;
	#endif
}

void addBall(){
	#ifdef PRINT
		cout<<"addBall() function called : Initially, threads.size() = "<<threads.size()<<endl;
	#endif
	addNewThread();
}

void setSpeedText(Ball &b){
	float speed = b.getSpeed();
	speed_str = to_string(speed);
	speed_text->set_text(speed_str.c_str());
}

void resetSpeedText(){
	speed_str = "No ball is selected";
	speed_text->set_text(speed_str.c_str());
}

void addNewThread(){
	Ball* b = createNewBall();

	queue<Ball*>* wq = new queue<Ball*>();
	
	MyThread* mthread = new MyThread(wq);
	mthread->setBall(b);
	threads.push_back(mthread);
	#ifdef PRINT
		cout<<"New Thread Added : threads.size() = "<<threads.size()<<endl;
	#endif
}

void addWorkItems(){
	queue<Ball*> *tq;
	int n = threads.size();
	int limit = n/2;
	for(int i=0;i<threads.size();i++){
		tq = threads[i]->getQueue();
		for(int j=0;j<limit;j++){
			tq->push(threads[(i+j+1)%n]->getBall());
		}
	}
}

float getRandomFloat(){
	int a,x;
	a = 1+rand()%2000;
	x = 2001 + rand()%2000;
	return float(a)/float(x);
}