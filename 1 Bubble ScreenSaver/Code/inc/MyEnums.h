/** @file
 * Enums are defined in this seperate file.
 */

#ifndef MyEnums_H_INCLUDED
#define MyEnums_H_INCLUDED

/** 
 * \defgroup TYPEDEFS Typedefs/Enums
 * @{
 */
enum GameState {PLAY,PAUSE};
extern GameState gameState;

enum Select{YES, NO};
extern Select border;
extern Select showMenu;
extern Select enable3D;
/** @} */

#endif