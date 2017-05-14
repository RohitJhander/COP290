/**
 * @file
 * Interface using GL user interface library, glui.h \n
 * All the changes to the menu should be added in this file only.
 */

#ifndef subMenu_H_INCLUDED
#define subMenu_H_INCLUDED

#include <GL/glut.h>
#include <GL/glui.h>
#include <string.h>

/** 
 * \defgroup GLUI_VARIABLES GLUI variables 
 * @{
 */
extern GLUI *glui;
extern int theme_group_item_id;
extern int theme_group_id;
extern int view_group_item_id;
extern int view_group_id;
extern int inc_id;
extern int dec_id;
extern int play_id;
extern int split_id;
extern int delete_id;
extern int add_id;
extern int window_id;
extern GLUI_Rotation *cube_rotate;
extern float cube_rotation[16];
extern std::string speed_str;
extern GLUI_StaticText *speed_text;
/** @} */

///glutIdleFunc
void myGlutIdle(void);

///Common call back function for all the menu buttons
void glui_callback(int);

///Initializes the menu. Adds panels, buttons and other items. \n
void initMenu();

#endif
