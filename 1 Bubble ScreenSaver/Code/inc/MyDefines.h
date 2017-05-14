/** @file
 * All the constants are defined here in seperate file.
 */

#ifndef MyDefines_H_INCLUDED
#define MyDefines_H_INCLUDED
/** \defgroup DEFINE Constants 
 * @{
 */

///Maximum number of balls possible on screen
#define MAX_NUM_BALLS 1000
///Minimum time before next ::update(int) function is called
#define UPDATE_TIMER 20
///Initial height of window
#define DEFAULT_WINDOW_HEIGHT 1056
///Initial width of window
#define DEFAULT_WINDOW_WIDTH 1855
///Initial Depth of box (in 3D view)
#define DEFAULT_WINDOW_DEPTH 600
///Time after which succesive balls enter the window
#define TIME_LAG 50
///Number of segment along and around z-axis of sphere
#define NUM_SEGMENTS 100
///Minimum width of window
#define LIMIT_W 500
///Minimum height of window
#define LIMIT_H 500
///Value of <a href="http://en.wikipedia.org/wiki/Pi">PI</a>
#define PI 3.1415926f
///Factor by which speed is increased/decreased on a single click on increase/decrease buttons
#define CHANGE_FACTOR 1.2f
///Max number of smaller balls on splitting a ball
#define MAX_SPLITS 7;
///Default view distance from the plane of drawing
#define zDistance 15.0f
///Time for which position of ball is changed in each update call
#define DT 0.5f
///Number of snow particles in the background
#define NUM_PARTICLES 1000
/** @} */

#endif