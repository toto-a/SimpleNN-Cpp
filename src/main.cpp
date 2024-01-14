#include "../include/Imshow.h"
#include "../include/ImFiltering.h"



int main(){
    

    Image img("image/plaque1.png");
    // img.write("src/a.png");
    Matrix kernel=Matrix{
        {-1.0f,0.0f,1.0f},
        {-2.0f,0.0f,2.0f},
        {-1.0f,0.0f,1.0f}
    }; 

       
    Image out=cv::Conv2d(img,kernel);
    // printf("Out shape Value %i %i\n",out.h, out.w) ;
    imshow("IMAGE",out);
    printf("Finsihed !");
    return 0;
}

