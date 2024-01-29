#include "../include/Imshow.h"
#include "../include/ImFiltering.h"
#include "../include/Tensor.h"



int main(){
    

    Image img("src/Lenna.png");
    Matrix kernel=Matrix{
        {-1.0f,0.0f,1.0f},
        {-2.0f,0.0f,2.0f},
        {-1.0f,0.0f,1.0f}
    }; 


       
    Image out=cv::Conv2d(img,kernel);
    Tensor ten=Tensor::zeros(2,2,3);
    Tensor sq=Tensor::matmul(ten,ten);
    Tensor teni=Image2Tensor(out);

    Tensor ten_t=ten.transpose();
    teni.printTensor();
    imshow("IMAGE",out);
    return 0;
}

