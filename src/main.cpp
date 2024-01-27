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
    Tensor ten=Image2Tensor(img);
    Tensor ten_t=ten.transpose();
    imshow("IMAGE",out);
    return 0;
}

