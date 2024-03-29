#include "../include/Tensor.h"
// 

Tensor::Tensor(unsigned int rows, unsigned int cols, unsigned int channels,float *data ){

  m_size=rows*cols*channels;
  m_channels=channels;
  m_data=new float[m_size];
    debug_message("Here");
  if (data){
    memcpy(m_data, data, m_size*sizeof(float));
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

  Tensor tp=zeros(m_rows,m_cols,m_channels);
  for(unsigned int b=0; b<m_channels; b++){
    for (unsigned int i=0; i<m_rows; i++){
        for (unsigned int j=0; j<m_cols ; j++){
              tp(i,j,b)=m_data[(j*m_rows+i)*tp.m_channels+b];
        }
      }
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

unsigned int Tensor::cols() const
{
    return m_cols;
}

unsigned int Tensor::rows() const
{
    return m_rows;
}

float * Tensor::data() const {
  return m_data;
}

float &Tensor::operator[](unsigned int index)
{

  if (index>=m_size){
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

std::string Tensor::Tensor2string()
{
    std::stringstream ss;
    for(unsigned int c=0;c<m_channels;c++){
      for( unsigned int i = 0; i < m_rows; i++){
        for(unsigned int j = 0; j < m_cols; j++){
            ss << std::setprecision(5) << m_data[(i*m_cols+j)*m_channels+c] << " ";
        }
        ss << std::endl;
      }
    }
    
    return ss.str();
}

void Tensor::printTensor()
{
  std::string ss=this->Tensor2string();
  std::cout<<ss<<std::endl;

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



Tensor Tensor::zeros_like(const Tensor &other)
{
    return zeros(other.m_rows,other.m_cols,other.m_channels);
}

Tensor Tensor::ones_like(const Tensor &other)
{
    return ones(other.m_rows,other.m_cols,other.m_channels);
}



Tensor Image2Tensor(const Image &img)
{ 
    Image in(img);
    unsigned int row=img.h;
    unsigned int cols=img.w;
    unsigned int channels=img.channels;

    float * fdata=new float[in.size];
    for(unsigned int b=0; b<channels; b++){
    for (unsigned int i=0; i<row; i++){
        for (unsigned int j=0; j<cols ; j++){
              fdata[(i*cols+j)*channels+b]=(float)1.0*in.data[(i*cols+j)*channels+b];
        }
      }
    }
    Tensor ten(row,cols,channels,fdata);
    delete[] fdata;

    return  ten;
}



void debug_message(const char *s)
{
  std::cout<<s<<std::endl;
}