/**
 * \class Image
 */

#ifndef imageLoad_H_INCLUDED
#define imageLoad_H_INCLUDED

///Represents a BMP image
class Image {
	public:
		///Constructor
		Image(char*, int, int);
		///Destructor
		~Image();
		///Pixel data of image
		char* data;
		///width and height of image
		int width, height;
};

//Reads the pixel data from a BMP file.
Image* loadImage(const char* filename);

#endif
