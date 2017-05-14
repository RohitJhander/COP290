#include <iostream>
#include <math.h>
#include <ctime>
#include <stdlib.h> 
#include <GL/glut.h>
#include <GL/glui.h>
#include <pthread.h>
#include <vector>
#include <queue>
#include <assert.h>
#include <string>

#include "mainw.h"
#include "Ball.h"
#include "Collision.h"
#include "Wall.h"
#include "Theme.h"
#include "imageLoad.h"
#include "thr.h"
#include "MyThread.h"
#include "themeReader.h"
#include "MyDefines.h"
#include "mainw.h"
#include "subMenu.h"
#include "MyEnums.h"
#include "UtilityFunctions.h"
#include "GUI.h"
#include "Particle.h"

using namespace std;

//Global variables

//window parameters
int window_height = 700;
int window_width = 700;

//GUI variables
float ALPHA = 0.0f;
float rotate = 0.0f;
float wideAngle = 30.0f;
float ratio = 1;
float viewDistance = zDistance/2;
float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;

int borderNumber = 0;
int number_of_balls = 10 ;

vector<MyThread*> threads;

Wall wall_x(YZ,DEFAULT_WINDOW_WIDTH),wall_y(XZ,DEFAULT_WINDOW_HEIGHT),wall_z(XY,DEFAULT_WINDOW_DEPTH);

vector<Theme *> themes;
Theme* curTheme;

//enum variables , enum defintions in MyEnums.h
GameState gameState = PLAY;
Select border = NO;
Select showMenu = NO;
Select enable3D = NO;

//GLUI variables
GLuint t1;
GLuint tex3d;
GLuint wall_tex;
GLUquadric *quad;
GLuint _textureId; //The id of the texture

Particle *particles;

int main(int argc, char** argv) {
	number_of_balls = stoi(argv[1]);
	#ifdef PRINT
		cout<<"Number of balls = "<<number_of_balls<<"\n";
	#endif

	if(number_of_balls < 0){
		cout<<"whoops , you made a mistake , number of balls can't be negative\n";
		exit(0);
	}

	if(number_of_balls > MAX_NUM_BALLS){
		cout<<"Maximum number of balls limit reached\n";
		exit(0);
	}

	srand(time(0));

	particles = new Particle[NUM_PARTICLES];
	
	preProcessTheme();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(DEFAULT_WINDOW_WIDTH,DEFAULT_WINDOW_HEIGHT); 
	window_id = glutCreateWindow("Screensaver");
	initRendering();

	initMenu();
	
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
   	glutMouseFunc(handleMouse);
	glutDisplayFunc(drawScene);
	glutTimerFunc(UPDATE_TIMER,update,number_of_balls*TIME_LAG);
	glutMainLoop();
	return 0; 
}
