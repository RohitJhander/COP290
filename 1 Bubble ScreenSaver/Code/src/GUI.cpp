#include "GUI.h"
#include "mainw.h"
#include "MyDefines.h"
#include "MyEnums.h"
#include "UtilityFunctions.h"
#include "subMenu.h"
#include "Particle.h"

#include <iostream>
using namespace std;

void handleMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		float xf = convPixel(x,y).first;
		float yf = convPixel(x,y).second;
		int clickedBall = findClickedBall(xf,yf);
		if (clickedBall == -1) {
			border = NO;
			resetSpeedText();
		} else {
			border = YES;
			borderNumber = clickedBall;
			setSpeedText(*(threads[borderNumber]->getBall()));
		}
		
	} else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		if (showMenu == YES) {
			showMenu = NO;
			glui->hide();
		} else {
			showMenu = YES;
			glui->show();
		}
	}
}

void handleResize(int w, int h) {
	int W = max(w,LIMIT_W);
	int H = max(h,LIMIT_H);
	window_height = H;
	window_width = W;
	GLUI_Master.auto_set_viewport();
	glViewport(0, 0, W, H);

	ratio = float(W)/float(H);
	wall_x.setPosition(ratio*zDistance*tanf(PI*wideAngle/360));
	wall_y.setPosition(zDistance*tanf(PI*wideAngle/360));
	wall_z.setPosition(zDistance/2);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(wideAngle,ratio,1.0,200.0);
}

void handleKeypress(unsigned char key,int x, int y) {  
	
	Ball* tempBall;
	
	switch(key){
		case 27:
			exit(0); 
		case 32:
			switch(gameState){
				case PLAY	:	gameState = PAUSE;	break;
				case PAUSE	: 	gameState = PLAY;	break;
				default		:	break;
			}
			break;
		case 100:
			tempBall = threads[borderNumber]->getBall();
			tempBall->setVelocity(tempBall->getVelocity().x+0.03f,tempBall->getVelocity().y, tempBall->getVelocity().z);
			setSpeedText(*tempBall);
			break;
		case 97:
			tempBall = threads[borderNumber]->getBall();
			tempBall->setVelocity(tempBall->getVelocity().x-0.03f,tempBall->getVelocity().y, tempBall->getVelocity().z);
			setSpeedText(*tempBall);
			break;
		case 119:
			tempBall = threads[borderNumber]->getBall();
			tempBall->setVelocity(tempBall->getVelocity().x,tempBall->getVelocity().y+0.03f, tempBall->getVelocity().z);
			setSpeedText(*tempBall);
			break;
		case 115:
			tempBall = threads[borderNumber]->getBall();
			tempBall->setVelocity(tempBall->getVelocity().x,tempBall->getVelocity().y-0.03f, tempBall->getVelocity().z);
			setSpeedText(*tempBall);
			break;
		case 49:
		case 50:
		case 51:
			setTheme(*themes[key-49]);
			break;
		case 52:
			if (enable3D == YES) enable3D = NO;
			else enable3D = YES;
		default:
			break;
	}
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); 
	glBindTexture(GL_TEXTURE_2D, textureId); 
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height,0, GL_RGB, GL_UNSIGNED_BYTE, image->data);     
	return textureId; 
}

void drawBox() {
	
	glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wall_tex);
		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor4f(1.0f, 1.0f, 1.0f,0.4f);
	
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-wall_x.getPosition(),-wall_y.getPosition(),-wall_z.getPosition());
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-wall_x.getPosition(), wall_y.getPosition(),-wall_z.getPosition());
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( wall_x.getPosition(), wall_y.getPosition(),-wall_z.getPosition());
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f( wall_x.getPosition(),-wall_y.getPosition(),-wall_z.getPosition());
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-wall_x.getPosition(),-wall_y.getPosition(), wall_z.getPosition());
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-wall_x.getPosition(), wall_y.getPosition(), wall_z.getPosition());
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( wall_x.getPosition(), wall_y.getPosition(), wall_z.getPosition());
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f( wall_x.getPosition(),-wall_y.getPosition(), wall_z.getPosition());
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-wall_x.getPosition(),-wall_y.getPosition(),-wall_z.getPosition());
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-wall_x.getPosition(), wall_y.getPosition(),-wall_z.getPosition());
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-wall_x.getPosition(), wall_y.getPosition(), wall_z.getPosition());
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-wall_x.getPosition(),-wall_y.getPosition(), wall_z.getPosition());
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f( wall_x.getPosition(),-wall_y.getPosition(),-wall_z.getPosition());
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f( wall_x.getPosition(), wall_y.getPosition(),-wall_z.getPosition());
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( wall_x.getPosition(), wall_y.getPosition(), wall_z.getPosition());
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f( wall_x.getPosition(),-wall_y.getPosition(), wall_z.getPosition());
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-wall_x.getPosition(),-wall_y.getPosition(),-wall_z.getPosition());
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f( wall_x.getPosition(),-wall_y.getPosition(),-wall_z.getPosition());
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( wall_x.getPosition(),-wall_y.getPosition(), wall_z.getPosition());
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-wall_x.getPosition(),-wall_y.getPosition(), wall_z.getPosition());
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-wall_x.getPosition(), wall_y.getPosition(),-wall_z.getPosition());
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f( wall_x.getPosition(), wall_y.getPosition(),-wall_z.getPosition());
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( wall_x.getPosition(), wall_y.getPosition(), wall_z.getPosition());
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-wall_x.getPosition(), wall_y.getPosition(), wall_z.getPosition());
	glEnd();
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	
	if (enable3D ==YES) {
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,tex3d);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glColor3f(1.0f, 1.0f, 1.0f);
		
		glBegin(GL_QUADS);	
		glNormal3f(0.0, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-ratio*100*tanf(PI*wideAngle/360), -100*tanf(PI*wideAngle/360), -100.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(ratio*100*tanf(PI*wideAngle/360), -100*tanf(PI*wideAngle/360), -100.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(ratio*100*tanf(PI*wideAngle/360), 100*tanf(PI*wideAngle/360), -100.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-ratio*100*tanf(PI*wideAngle/360), 100*tanf(PI*wideAngle/360), -100.0f);
		glEnd();
		
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
	}
	
	
	glTranslatef(0.0f, 0.0f, -zDistance);
	
	if (enable3D == YES) {
		glTranslatef(0.0f,0.0f,-viewDistance);
		glMultMatrixf(cube_rotation);
		} else {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _textureId);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glColor3f(1.0f, 1.0f, 1.0f);
		
		glBegin(GL_QUADS);	
		glNormal3f(0.0, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-wall_x.getPosition(), -wall_y.getPosition(), -0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(wall_x.getPosition(), -wall_y.getPosition(), -0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(wall_x.getPosition(), wall_y.getPosition(), -0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-wall_x.getPosition(), wall_y.getPosition(), -0.0f);
		glEnd();
		
		glDisable(GL_TEXTURE_2D);
	}
	
	GLfloat lightColor0[] = {curTheme->clr[0].r, curTheme->clr[0].g, curTheme->clr[0].b, 1.0f};
	GLfloat lightPos0[] = {curTheme->pos[0].x, curTheme->pos[0].y, curTheme->pos[0].z, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	GLfloat lightColor1[] = {curTheme->clr[1].r, curTheme->clr[1].g, curTheme->clr[1].b, 1.0f};
	GLfloat lightPos1[] = {curTheme->pos[1].x, curTheme->pos[1].y, curTheme->pos[1].z, 1.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	
	GLfloat lightColor2[] = {curTheme->clr[2].r, curTheme->clr[2].g, curTheme->clr[2].b, 1.0f};
	GLfloat lightPos2[] = {curTheme->pos[2].x, curTheme->pos[2].y, curTheme->pos[2].z, 1.0f};
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
	
	//Draw Balls here
   	for(int i=0;i<threads.size(); i++) {
		threads[i]->getBall()->Draw(NUM_SEGMENTS);
	}

	if(enable3D == NO){
		for(int j=0; j<NUM_PARTICLES; j++) {
			particles[j].drawP();
		}
	}

	if(enable3D==YES){
		drawBox();
	}
	
	if(border == YES) {
		Ball* tempBall = threads[borderNumber]->getBall();
		setSpeedText(*tempBall);
		glPushMatrix();
		glTranslatef(tempBall->getCenter().x,
						tempBall->getCenter().y,
						tempBall->getCenter().z);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA , GL_DST_ALPHA);
		Color clr = tempBall->getColor();
		glColor4f(clr.r,clr.g,clr.b,0.5);
		glutSolidSphere(tempBall->getRadius()*1.2f,20,20);
		glDisable(GL_BLEND);
		glPopMatrix();
	}
	
	glutSwapBuffers(); 
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	setTheme(*curTheme);
	glEnable(GL_NORMALIZE);
	
	Image* image = loadImage(curTheme->image.c_str());
	_textureId = loadTexture(image);
	delete image;

	quad = gluNewQuadric();
	Image* image1 = loadImage("files/ball1.bmp");
	t1 = loadTexture(image1);
	delete image1;
	
	Image* image2 = loadImage("files/3d.bmp");
	tex3d = loadTexture(image2);
	delete image2;
	
	Image* image3 = loadImage("files/wall.bmp");
	wall_tex = loadTexture(image3);
	delete image3;
}

void update(int value) {
	if(gameState == PLAY){
		if(value > 0) {
			if(value%TIME_LAG == 0){
				addNewThread();
			}
			value--;
		}
		
		for(int j=0;j<NUM_PARTICLES; j++) {
			particles[j].moveP();
		}

		for(int i=0 ; i<threads.size(); i++){
			threads[i]->getBall()->Move(DT);
		}
		
		for(int i=0;i<threads.size();i++) {
			int rc = threads[i]->start();
			if(rc){
				cout<<"can not create thread, id = "<<i<<endl;
				exit(0);
			}
		}
		
		for(int i=0;i<threads.size();i++){
			int rc = threads[i]->join();
			if(rc){
				cout<<"can not join thread, id = "<<i<<endl;
				exit(0);
			}
		}
		addWorkItems();
	}
	glutPostRedisplay();
	glutTimerFunc(UPDATE_TIMER,update,value);
}