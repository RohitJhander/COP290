/**
 * @file
 * Changes in this and class @link Theme.h should be in sync
 */

#ifndef themeReader_H_INCLUDED
#define themeReader_H_INCLUDED

#include <vector>
#include <fstream>
#include <iostream>
#include "Theme.h"

///Loads different theme from themeFile.txt into a vector .
vector<Theme*> readThemes(const char* filename);
///utility to read a bool from file
bool readBool(ifstream& fin);
///utility to read a float from file
float readFloat(ifstream& fin);

#endif
