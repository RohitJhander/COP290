#include "themeReader.h"
#include <iostream>

using namespace std;

vector<Theme*> readThemes(const char* filename){
	vector<Theme* > toReturn;
	ifstream fin;
	fin.open(filename,ios::in);
	char ch;
	while(fin.get(ch)){
		if(ch=='#')
			break;
		
		fin.seekg(-1,ios::cur);
		Theme* newTheme  = new Theme();

		for(int i=0;i<4;i++){
			newTheme->isLight[i] = readBool(fin);	fin.ignore(1);
		}

		newTheme->background.r = readFloat(fin);	fin.ignore(1);
		newTheme->background.g = readFloat(fin);	fin.ignore(1);
		newTheme->background.b = readFloat(fin);	fin.ignore(1);
		
		for(int i=0;i<3;i++){
			newTheme->clr[i].r = readFloat(fin);	fin.ignore(1);
			newTheme->clr[i].g = readFloat(fin);	fin.ignore(1);
			newTheme->clr[i].b = readFloat(fin);	fin.ignore(1);
		}

		for(int i=0;i<3;i++){
			newTheme->pos[i].x = readFloat(fin);	fin.ignore(1);
			newTheme->pos[i].y = readFloat(fin);	fin.ignore(1);
			newTheme->pos[i].z = readFloat(fin);	fin.ignore(1);
		}
		string s;
		fin>>s;
		newTheme->image = s;
		fin.ignore(1);
		toReturn.push_back(newTheme);
	}
	return toReturn;
}

bool readBool(ifstream& fin){
	char ch;
	fin.get(ch);
	return (ch=='0' ? false:true);
}

float readFloat(ifstream& fin){
	char ch;
	bool neg = false;
	float toReturn = 0.0;
	fin.get(ch);
	if(ch=='-'){
		neg = true;
	}else{
		fin.seekg(-1,ios::cur);
	}
	fin>>toReturn;
	if(neg)
		toReturn = -toReturn;

	return toReturn;
}