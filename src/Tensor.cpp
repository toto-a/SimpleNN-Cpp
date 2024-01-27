#include "../include/Tensor.h"
#include "Tensor.h"


Tensor::Tensor(unsigned int rows, unsigned int cols, unsigned int channels,float *data ){

  m_size=rows*cols*channels;
  float* new_data=new float[m_size];
  if (data){
    std::memcpy(new_data, data, m_size*sizeof(float));
    std::cout<<"Type of data :"<< typeid(data).name()<<std::endl;
  }
  else{
    int val=0;
    memset(new_data,val,m_size*sizeof(float));
  }
  m_cols=cols;
  m_rows=rows;
}

void Tensor::isMatmutable(const Tensor &a, const Tensor &b)
{
  if (a.m_cols!=b.m_rows){
      printf("The size of tensor a %u must match the size of tensor b %u at non-singleton dimension 0",
      a.m_cols,b.m_rows );
      throw 0;
  }
  else if (a.m_channels!=b.m_channels){

    printf("The size of tensor a %u must match the size of tensor b %u at non-singleton dimension 0",
    a.m_channels,b.m_channels);
    throw 0;
  }
}

void Tensor::inBound(const Tensor& a,unsigned int x, unsigned int y)
{
  if((x>= a.m_rows) | (y >= a.m_cols)){
    printf("Out of bounds  ");
    throw 0;
  }
}

void Tensor::sameSize(const Tensor &a, const Tensor &b)
{
  if(a.m_size!=b.m_size){
    printf("Tensor must be of the same size ! Found %lu and %lu ", a.m_size, b.m_size);
    throw 0;
  }

}

Tensor Tensor::transpose(){

  Tensor tp(m_cols,m_rows,m_channels);
  for(unsigned int i=0; i<m_size;i++){
      int j=(i%m_cols);
      int l=(i%m_rows);
      tp[i]=m_data[(j*m_rows)+l];
    
  } 
  
  return tp;
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

  if (index>m_size){
    printf("Index out of bound : size %ld and index %u",m_size,index);
    throw 0;
  }
  return m_data[index];
}

float &Tensor::operator()(unsigned int x, unsigned int y, unsigned int z) const
{
    inBound(*this,x,y);
    return m_data[(x*m_cols+y)*z];
}

std::string Tensor::printTensor()
{
    std::stringstream ss;
    for(unsigned int i=0; i<m_size; i++){
      ss<<std::setprecision(2)<< m_data[i]<< " ";

    }
    ss<<std::endl;
    return ss.str();
}

Tensor Tensor::operator+(const Tensor &other)
{
    sameSize(*this,other);
    Tensor result=this->copy();
    for (unsigned int i=0; i<m_size;i++){
      result.m_data[i]+=m_data[i];
    }

    return result;
}

Tensor Tensor::operator+(const float c)
{
    Tensor result=this->copy();
    for (unsigned int i=0; i<m_size;i++){
      result.m_data[i]+=c;
    }

    return result;
}

Tensor Tensor::operator-(const Tensor &other)
{
    sameSize(*this,other);
    Tensor result=this->copy();
    for (unsigned int i=0; i<m_size;i++){
      result.m_data[i]-=m_data[i];
    }

    return result;
 
}

Tensor Tensor::operator-(const float c)
{
    Tensor result=this->copy();
    for (unsigned int i=0; i<m_size;i++){
      result.m_data[i]-=c;
    }

    return result;
}

Tensor Tensor::operator*(const Tensor &other)
{
    sameSize(*this,other);
    Tensor result=this->copy();
    for (unsigned int i=0; i<m_size;i++){
      result.m_data[i]*=m_data[i];
    }

    return result;
 
}

Tensor Tensor::operator*(const float c)
{ 
    Tensor result=this->copy();
    for (unsigned int i=0; i<m_size;i++){
      result.m_data[i]-=c;
    }

    return result;
}


Tensor Tensor::zeros(unsigned int rows, unsigned int cols, unsigned int channels){
  Tensor zen(rows, cols,channels);
  size_t size=rows*cols*channels;
  for(unsigned int i=0;i<size;i++){
    zen[i]=0;
  }
  return zen;
}

Tensor Tensor::ones(unsigned int rows, unsigned int cols, unsigned int channels){
  Tensor one(rows, cols,channels);
  size_t size=rows*cols*channels;
  for(unsigned int i=0;i<size;i++){
    one[i]=1;
  }
  return one;
}


Tensor Tensor::range(unsigned int rows, unsigned int cols, unsigned int channels){

  Tensor ran(rows, cols,channels);
  size_t size=rows*cols*channels;
  for(unsigned int i=0;i<size;i++){
    ran[i]=i;
  }
  return ran;
}


Tensor Tensor::randn(unsigned int rows, unsigned int cols, unsigned int channels){
    Tensor n(rows,cols,channels);
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::normal_distribution<float>d(0,1);
    
    for(unsigned int i=0; i<n.m_size; i++){
        n[i]=d(gen);
    }
    
  return n;
}

Tensor Image2Tensor(const Image &img)
{ 
    unsigned int row=img.h;
    unsigned int cols=img.w;
    unsigned int channels=img.channels;
    float* data = static_cast<float*>(static_cast<void*>(img.data));
    Tensor ten(row,cols,channels,data);

    return  ten;


}