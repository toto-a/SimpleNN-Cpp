#ifndef TENSOR_CLASS_H
#define TENSOR_CLASS_H



#include "../include/Image.h"
#include <string>
#include <cstring>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <typeinfo>
#include <typeinfo>


class Tensor  
{
  public:
    Tensor(unsigned int rows, unsigned int cols, unsigned int channels,float *data=nullptr );
    Tensor copy();
    Tensor transpose();
     
    static Tensor matmul(const Tensor&A, const Tensor&B);
    unsigned int cols() const;
    unsigned int rows() const;
    float* data() const;

    static Tensor zeros(unsigned int rows, unsigned int cols, unsigned int channels);
    static Tensor ones(unsigned int rows, unsigned int cols, unsigned int channels);
    static Tensor range(unsigned int rows, unsigned int cols, unsigned int channels);
    static Tensor randn(unsigned int rows, unsigned int cols, unsigned int channels);

    static Tensor zeros_like(const Tensor &other);
    static Tensor ones_like(const Tensor &other);


    // Operators
    Tensor operator+(const Tensor &other);
    Tensor operator+(const float c); //broadcast
    Tensor operator-(const Tensor &other);
    Tensor operator-(const float c);
    Tensor operator*(const Tensor &other);
    Tensor operator*(const float c);

    float& operator[](unsigned int index);
    float& operator()(unsigned int x, unsigned int y,unsigned int z) const;

    std::string Tensor2string();
    void printTensor();

    
    private:

      static void isMatmutable(const Tensor& a, const Tensor& b );
      static void inBound(const Tensor& a, unsigned int x, unsigned int y);
      static void sameSize(const Tensor& a, const Tensor& b);
 

      float* m_data;
      unsigned int m_rows;
      unsigned int m_cols;
      unsigned int m_channels;
      size_t m_size=0;


};


Tensor Image2Tensor(const Image& img);
void debug_message(const char * s);
  

#endif
