#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define BYTE_BOUND(value) value < 0 ? 0 : (value > 255 ? value%256 : value)

#include "../include/stb_image.h"
#include "../include/stb_image_write.h"
#include "../include/Image.h"
#include "Image.h"

Image::Image(const char* filename) {
	if(read(filename)) {
		printf("Read %s\n", filename);
		size = w*h*channels;
	}
	else {
		printf("Failed to read %s\n", filename);
	}
}

Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) {
	size = w*h*channels;
	data = new uint8_t[size];
}

Image::Image()  
{
	
}

Image::Image(const Image& img) : Image(img.w, img.h, img.channels) {
	memcpy(data, img.data, size);
}

Image::~Image() {
	stbi_image_free(data);
}

bool Image::read(const char* filename) {
	
	data = stbi_load(filename, &w, &h, &channels, 0);
	return data != NULL;
}


bool Image::write(const char* filename) {
	ImageType type = get_file_type(filename);
	int success;
  switch (type) {
    case PNG:
      success = stbi_write_png(filename, w, h, channels, data, w*channels);
      break;
    case BMP:
      success = stbi_write_bmp(filename, w, h, channels, data);
      break;
    case JPG:
      success = stbi_write_jpg(filename, w, h, channels, data, 100);
      break;
    case TGA:
      success = stbi_write_tga(filename, w, h, channels, data);
      break;
  }
  if(success != 0) {
    return true;
  }
  else {
    // printf("\e[31;1m Failed to write \e[36m%s\e[0m, %d, %d, %d, %zu\n", filename, w, h, channels, size);
    return false;
  }
}

u8 Image::at_(int x, int y, int c)
{

  float value= data[(x*w+y)*channels+c];
  return value;
}

void Image::alloc_val(int x,int y,int c,u8 value){

	data[(x*w+y)*channels+c]=value;

}

Image& Image::copy_(Image &out)
{
	//Create a zero filled image with the same characterisitcs of the input image
	if (out.size!=size){
		std::cerr<< "Size doesn't match !, Copy Impossible "<<std::endl;
		return *this;
	}
	Image copy(out);
	data=copy.data;
	copy.data=nullptr;

	return *this;
}



ImageType Image::get_file_type(const char *filename)
{
    const char* ext = strrchr(filename, '.');
	if(ext != nullptr) {
		if(strcmp(ext, ".png") == 0) {
			return PNG;
		}
		else if(strcmp(ext, ".jpg") == 0) {
			return JPG;
		}
		else if(strcmp(ext, ".bmp") == 0) {
			return BMP;
		}
		else if(strcmp(ext, ".tga") == 0) {
			return TGA;
		}
	}
	return PNG;
}

Image& Image::grayscale_avg() {
	if(channels < 3) {
		printf("Image %p has less than 3 channels, it is assumed to already be grayscale.", this);
	}
	else {
		for(unsigned int i = 0; i < size; i+=channels) {
			//(r+g+b)/3
			int gray = (data[i] + data[i+1] + data[i+2])/3;
			memset(data+i, gray, 3);
		}
	}
	return *this;
}


Image& Image::grayscale_lum() {
	if(channels < 3) {
		printf("Image %p has less than 3 channels, it is assumed to already be grayscale.", this);
	}
	else {
		for(long unsigned int i = 0; i < size; i+=channels) {
			int gray = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
			memset(data+i, gray, 3);
		}
	}
	return *this;
}







Image& Image::flipY() {

  uint8_t tmp[4];
  uint8_t* px1;
  uint8_t* px2;
	for(int x = 0;x < w;++x) {
		for(int y = 0;y < h/2;++y) {
			px1 = &data[(x + y * w) * channels];
			px2 = &data[(x + (h - 1 - y) * w) * channels];

			memcpy(tmp, px1, channels);
			memcpy(px1, px2, channels);
			memcpy(px2, tmp, channels);
		}
	}
	return *this;
}




Image& Image::crop(uint16_t cx, uint16_t cy, uint16_t cw, uint16_t ch) {
	size = cw * ch * channels;
	uint8_t* croppedImage = new uint8_t[size];
	memset(croppedImage, 0, size);

	for(uint16_t y = 0;y < ch;++y) {
		if(y + cy >= h) {break;}
		for(uint16_t x = 0;x < cw;++x) {
			if(x + cx >= w) {break;}
			memcpy(&croppedImage[(x + y * cw) * channels], &data[(x + cx + (y + cy) * w) * channels], channels);
		}
	}

	w = cw;
	h = ch;
	

	delete[] data;
	data = croppedImage;
	croppedImage = nullptr;

	return *this;
}


Image & Image::malloc(Image & img){
	
  delete[] data;
	h=img.h;
	w=img.w;
	channels=img.channels;

	data=new u8[img.size];	
	// data=new float[img.size];	
	memcpy(data,img.data,img.size);

	return *this;


}

Image zeros_like(const Image &img)
{
	Image out(img);
	memset(out.data,0,out.size);
  return out;

}
