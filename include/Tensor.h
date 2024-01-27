#ifndef TENSOR_CLASS_H
#define TENSOR_CLASS_H



#include "../include/Image.h"


class Tensor  
{
  public:
    Tensor(unsigned int rows, unsigned int cols, unsigned int channels,float *data=nullptr );
    Tensor copy();
    Tensor transpose();
     
    static Tensor matmul(const Tensor&A, const Tensor&B);

    static Tensor zeros(unsigned int rows, unsigned int cols, unsigned int channels);
    static Tensor ones(unsigned int rows, unsigned int cols, unsigned int channels);
    static Tensor range(unsigned int rows, unsigned int cols, unsigned int channels);
    static Tensor randn(unsigned int rows, unsigned int cols, unsigned int channels);


    // Operators
    Tensor operator+(const Tensor &other);
    Tensor operator+(const float c); //broadcast
    Tensor operator-(const Tensor &other);
    Tensor operator-(const float c);
    Tensor operator*(const Tensor &other);
    Tensor operator*(const float c);

    float& operator[](unsigned int index);
    float& operator()(unsigned int x, unsigned int y,unsigned int z) const;

    
    private:

      static void isMatmutable(const Tensor& a, const Tensor& b );
      static void inBound(const Tensor& a, unsigned int x, unsigned int y);
      static void sameSize(const Tensor& a, const Tensor& b);
 

      float* m_data;
      unsigned int m_rows;
      unsigned int m_cols;
      unsigned int m_channels;
      size_t size=m_rows*m_cols*m_channels;


};


inline Tensor Image2Tensor(const Image& img){
    unsigned int row=img.h;
    unsigned int cols=img.w;
    unsigned int channels=img.channels;
    float * data=reinterpret_cast<float*>(img.data);
    Tensor ten(row,cols,channels,data);

    return  ten;

}

#endif
