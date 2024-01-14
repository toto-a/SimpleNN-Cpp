#ifndef IMAGE_CLASS_H
#define IMAGE_CLASS_H




#include <stdint.h>
#include <cstdio>
#include <stdexcept>
#include <cstring>
#include <complex>
#include <iostream>
#include <vector>


#undef __STRICT_ANSI__
#define _USE_MATH_DEFINES 
#include <cmath>
#ifndef M_PI
	#define M_PI (3.14159265358979323846)
#endif


#define STEG_HEADER_SIZE sizeof(uint32_t) * 8

typedef uint8_t u8;
typedef std::vector<double> Array;
typedef std::vector<Array> Matrix;
typedef std::vector<Matrix> fImage;



enum ImageType{
	PNG,JPG,BMP,TGA
};


struct Image {
	uint8_t* data = NULL;
	// float* data = NULL;
	size_t size = 0;
	int w;
	int h;
	int channels;

	Image(const char* filename);
	Image(int w, int h, int channels );
	Image();
	Image(const Image& img);
	~Image();

	bool read(const char* filename) ;
	bool write(const char* filename);
	u8 at_(int x,int y,int c);
	void alloc_val(int x, int y, int c,u8 value);
	Image& copy_(Image& out);
	

	ImageType get_file_type(const char* filename);
	Image& grayscale_avg();
	Image& grayscale_lum();
	

	Image& flipY();
	Image& crop(uint16_t cx, uint16_t cy, uint16_t cw, uint16_t ch);
	Image& malloc( Image& img);


};


Image zeros_like(const Image& img);


#endif