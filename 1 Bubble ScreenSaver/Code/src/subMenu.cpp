#include "subMenu.h"

#include <stdlib.h>
#include "Theme.h"
#include "MyDefines.h"
#include "Ball.h"
#include "MyEnums.h"
#include "UtilityFunctions.h"
#include "mainw.h"
#include "GUI.h"

using namespace std;

//extern declarations

GLUI *glui;
int theme_group_item_id;
int theme_group_id=0;
int view_group_item_id;
int view_group_id=3;
int inc_id = 1;
int dec_id = 2;
int play_id = 4;
int split_id = 5;
int delete_id = 6;
int add_id = 7;
int window_id;
GLUI_Rotation *cube_rotate;
float cube_rotation[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
string speed_str = "No ball is selected";
GLUI_StaticText *speed_text;

void myGlutIdle(void){
	glutSetWindow(window_id);
	glutPostRedisplay();
}

void glui_callback(int id){
	switch(id)
	{
		case 0:
			setTheme(*themes[theme_group_item_id]);
			break;
		case 1:
			if (border == YES){
				Ball* tempBall = threads[borderNumber]->getBall();
				changeVelocity(*tempBall, CHANGE_FACTOR);
				setSpeedText(*tempBall);
			}else{
				for(int i=0;i<threads.size();i++) {
					changeVelocity(*(threads[i]->getBall()), CHANGE_FACTOR);
				}
			}
			break;
		case 2:
			if (border == YES){
				Ball* tempBall = threads[borderNumber]->getBall();
				changeVelocity(*tempBall,1.0f/CHANGE_FACTOR);
				setSpeedText(*tempBall);
			}else{
				for(int i=0;i<threads.size();i++) {
					changeVelocity(*(threads[i]->getBall()),1.0/CHANGE_FACTOR);
				}
			}
			break;
		case 3:
			if (view_group_item_id == 1){
				enable3D = YES;
				for(int i=0 ; i<threads.size() ; i++){
					float temp = getRandomFloat();
					if(rand()%20 < 10){
						temp = -temp;
					}
					ThreeD vel = threads[i]->getBall()->getVelocity();
					threads[i]->getBall()->setVelocity(vel.x , vel.y ,temp);
				}
			}
			else {
				enable3D = NO;
				for(int i=0 ; i<threads.size() ; i++){
					ThreeD vel = threads[i]->getBall()->getVelocity();
					ThreeD ctr = threads[i]->getBall()->getCenter();
					threads[i]->getBall()->setVelocity(vel.x , vel.y , 0.0f);
					threads[i]->getBall()->setCenter(ctr.x , ctr.y , 0.0f);
				}
			}
			break;
		case 4:
			switch(gameState){
				case PLAY	:	gameState = PAUSE;	break;
				case PAUSE	: 	gameState = PLAY;	break;
				default		:	break;
			}
			break;
		case 5:
			if (border == YES) {
				int n = rand() % MAX_SPLITS;
				splitBall(*(threads[borderNumber]->getBall()), n+1);
				border = NO;
				resetSpeedText();
			}
			break;
		case 6:
			if (border == YES) {
				deleteBall(borderNumber);
				border = NO;
				resetSpeedText();
			}
			break;
		case 7:
			addBall();
			break;
		default:
			break;
	}
}

void initMenu(){
	GLUI_Master.set_glutIdleFunc(myGlutIdle);
	GLUI_Master.set_glutReshapeFunc(handleResize);
	GLUI_Master.set_glutKeyboardFunc(handleKeypress);
	GLUI_Master.set_glutMouseFunc(handleMouse);

	glui = GLUI_Master.create_glui_subwindow(window_id, GLUI_SUBWINDOW_RIGHT);
	GLUI_Rollout *theme_rollout = glui->add_rollout("Themes");
	GLUI_RadioGroup *theme_group = glui->add_radiogroup_to_panel(theme_rollout, &theme_group_item_id, theme_group_id, glui_callback);
	glui->add_radiobutton_to_group(theme_group, "Theme1" );
	glui->add_radiobutton_to_group(theme_group, "Theme2" );
	glui->add_radiobutton_to_group(theme_group, "Theme3" );

	glui->add_separator();
	
	GLUI_Rollout *view_rollout = glui->add_rollout("View");
	GLUI_RadioGroup *view_group = glui->add_radiogroup_to_panel(view_rollout, &view_group_item_id, view_group_id, glui_callback);
	glui->add_radiobutton_to_group(view_group, "2D" );
	glui->add_radiobutton_to_group(view_group, "3D" );

	glui->add_separator();
	
	GLUI_Panel *speed_panel = glui->add_panel ("Controls");
	glui->add_button_to_panel(speed_panel,"Play/Pause",play_id,glui_callback);
	glui->add_button_to_panel(speed_panel,"Increase Speed",inc_id,glui_callback);
	glui->add_button_to_panel(speed_panel,"Decrease Speed",dec_id,glui_callback);
	glui->add_button_to_panel(speed_panel,"Split Ball",split_id,glui_callback);
	glui->add_button_to_panel(speed_panel,"Add Ball",add_id,glui_callback);
	glui->add_button_to_panel(speed_panel,"Delete Ball",delete_id,glui_callback);

	glui->add_separator();

	GLUI_Panel *text_panel = glui->add_panel ("Speed of selected ball");
	GLUI_StaticText *blank = glui->add_statictext_to_panel(text_panel,"    ");
	speed_text = glui->add_statictext_to_panel(text_panel,speed_str.c_str());
	
	glui->add_separator();

	cube_rotate = new GLUI_Rotation(glui, "Rotate", cube_rotation);
	cube_rotate->set_spin(1.0);

	glui->add_separator();

	GLUI_Translation *trans_z = new GLUI_Translation( glui, "Zoom IN/OUT", GLUI_TRANSLATION_Z, &viewDistance);
	glui->hide();
	glui->sync_live();
	glui->set_main_gfx_window( window_id );
}
