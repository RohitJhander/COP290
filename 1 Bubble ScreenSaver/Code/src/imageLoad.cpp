#include <fstream>
#include <assert.h>

#include "imageLoad.h"

using namespace std;

Image::Image(char* d , int w, int h) : data(d), width(w), height(h) {}

Image::~Image() {
	delete []data;
}

int toInt(const char* bytes) {
	return (int)(((unsigned char)bytes[3] << 24) |
				 ((unsigned char)bytes[2] << 16) |
				 ((unsigned char)bytes[1] << 8) |
				 (unsigned char)bytes[0]);
}

short toShort(const char* bytes) {
	return (short)(((unsigned char)bytes[1] << 8) |
				   (unsigned char)bytes[0]);
}

int readInt(ifstream &fin) {
	char buffer[4];
	fin.read(buffer, 4);
	return toInt(buffer);
}

short readShort(ifstream &fin) {
	char buffer[2];
	fin.read(buffer, 2);
	return toShort(buffer);
}

Image* loadImage(const char* filename) {
	ifstream fin;
	fin.open(filename, ios::binary);
	
	assert(!fin.fail() || !"Could not find file");
	char buffer[2];
	fin.read(buffer, 2);
	assert((buffer[0] == 'B' && buffer[1] == 'M') || !"Not a bitmap file");
	fin.ignore(8);
	int dataOffset = readInt(fin);
	
	//Read the header
	int headerSize = readInt(fin);
	int width;
	int height;
	width = readInt(fin);
	height = readInt(fin);
	fin.ignore(2);
	assert(readShort(fin) == 24 || !"Image is not 24 bits per pixel");
	assert(readShort(fin) == 0 || !"Image is compressed");
	
	//Read the data
	int size = width * height * 3;
	char* data = new char[size];
	fin.seekg(dataOffset, ios_base::beg);
	fin.read(data, size);

	char* toReturn = new char[size];

	//swap the red and blue components
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			for(int k=0;k<3;k++){
				toReturn[3*(width*i+j)+k] = data[3*(width*i+j)+2-k];
			}
		}
	}

	delete[] data;
	
	fin.close();
	return new Image(toReturn, width, height);
}
