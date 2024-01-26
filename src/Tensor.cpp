#include "../include/Tensor.h"
#include "Tensor.h"





Tensor::Tensor(unsigned int rows, unsigned int cols, unsigned int channels,float *data=nullptr){

  size_t size=rows*cols*channels;
  float* new_data=new float[size];
  if (data){
    std::memcpy(new_data, data, size*sizeof(float));
  }
  m_cols=cols;
  m_rows=rows;
}

void Tensor::isMatmutable(const Tensor &a, const Tensor &b)
{
  if (a.m_cols!=b.m_rows){
      printf("The size of tensor a %u must match the size of tensor b %u at non-singleton dimension 0",a.m_cols,b.m_rows );
      throw 0;
  }
  else if (a.m_channels!=b.m_channels){

    printf("The size of tensor a %u must match the size of tensor b %u at non-singleton dimension 0",a.m_channels,b.m_channels);
    throw 0;
  }
}

void Tensor::inBound(const Tensor& a,unsigned int x, unsigned int y)
{
  if(x>= a.m_rows | y >= a.m_cols){
    printf("Out of bounds % ");
    throw 0;
  }
}

void Tensor::sameSize(const Tensor &a, const Tensor &b)
{
  if(a.size!=b.size){
    printf("Tensor must be of the same size ! Found %u and %u ", a.size, b.size);
    throw 0;
  }

}



Tensor Tensor::copy(){
  Tensor copy=Tensor(m_rows,m_cols,m_channels,m_data);
  return copy;
}

Tensor Tensor::matmul(const Tensor &A, const Tensor &B)
{
    isMatmutable(A,B);
    unsigned int n=A.m_rows;
    unsigned int m=B.m_cols;
    unsigned int batch_dim=A.m_channels;
    unsigned int K=B.m_rows;
    Tensor out=Tensor(n,m,batch_dim);
    for(unsigned int b=0; b<batch_dim; b++){
      for(unsigned int k=0; k<K; k++){
        for (unsigned int i=0; i<n; i++){
          for (unsigned int j=0; j<m ; j++){
              out(i,j,b)=A(i,k,b)*B(k,j,b);
          }
        }
      }
    }

    return out;
}



float &Tensor::operator[](unsigned int index)
{

  if (index>size){
    printf("Index out of bound : size %s and index %u",size,index);
    throw 0;
  }
  return m_data[index];
}

float &Tensor::operator()(unsigned int x, unsigned int y, unsigned int z) const
{
    inBound(*this,x,y);
    return m_data[(x*m_cols+y)*z];
}

Tensor Tensor::operator+(const Tensor &other)
{
    sameSize(*this,other);
    Tensor result=this->copy();
    for (unsigned int i=0; i<size;i++){
      result.m_data[i]+=m_data[i];
    }

    return result;
}

Tensor Tensor::operator+(const float c)
{
    Tensor result=this->copy();
    for (unsigned int i=0; i<size;i++){
      result.m_data[i]+=c;
    }

    return result;
}

Tensor Tensor::operator-(const Tensor &other)
{
    sameSize(*this,other);
    Tensor result=this->copy();
    for (unsigned int i=0; i<size;i++){
      result.m_data[i]-=m_data[i];
    }

    return result;
 
}

Tensor Tensor::operator-(const float c)
{
    Tensor result=this->copy();
    for (unsigned int i=0; i<size;i++){
      result.m_data[i]-=c;
    }

    return result;
}

Tensor Tensor::operator*(const Tensor &other)
{
    sameSize(*this,other);
    Tensor result=this->copy();
    for (unsigned int i=0; i<size;i++){
      result.m_data[i]*=m_data[i];
    }

    return result;
 
}

Tensor Tensor::operator*(const float c)
{ 
    Tensor result=this->copy();
    for (unsigned int i=0; i<size;i++){
      result.m_data[i]-=c;
    }

    return result;
}
