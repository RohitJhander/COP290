/**
 * \class Theme
 * Changes in this and @link themeReader.h should be in sync
 */

#ifndef THEME_H_INCLUDED
#define THEME_H_INCLUDED

#include "global.h"
#include <string>
using namespace std;

///To store features of theme
class Theme {
	public:
		///Theme with default settings
		Theme(){}
		///Background color
		Color background;
		///Lighting color
		Color clr[3];
		///Lights position
		ThreeD pos[3];
		///Enable/Disable Light
		bool isLight[4];
		///Background Image
		string image;
};

#endif
