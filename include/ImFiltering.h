#ifndef IMFILTERING_CLASS_H
#define IMFILTERING_CLASS_H



#include "../include/Image.h"



namespace cv{


Image padding(Image& img,int kw, int kh){    
    
    int out_w=img.w + kw -1;
    int out_h=img.h + kh -1;
    int out_channels=img.channels;

    Image out(out_w,out_h,out_channels);

    

    for(int c=0; c<img.channels; c++){
        for(int x=0;x<img.h;x++){
            for(int y=0; y<img.w; y++){
                int out_x=x+kh;
                int out_y=y+kw;

                if((out_x>=0 && out_x<out_h) &&(out_y>=0 && out_y<out_w)){

                    out.data[(out_x*out_w+out_y)*out_channels+c]=img.data[(x*img.w+y)*out_channels+c];
                }


            }
        }
    }

    return out;
}




Image convolution_full(Image& img, Matrix& kernel){
    int kh=kernel.size();
    int kw=kernel[0].size();
    Image out=cv::padding(img,kw,kh);
    for(int c=0; c<out.channels; c++){
        for(int x=0;x<img.h;x++){

            for(int y=0; y<img.w; y++){
                u8 val=0;
                for(int i=x-kh/2; i<=x+kh/2 ; i++){
                    for(int j=y-kw/2; j<=y+kw/2  ;j++){
                        

                        if((i>=0 && i<img.h) &&(j>=0 && j<img.w) ){
                        
                            val+=kernel[i-(x-kh/2)][j-(y-kw/2)]*img.data[(i*img.w+j)*out.channels+c];
                        
                        }
                    }

                    out.alloc_val(x,y,c,val);

                }



            }
        }
    }
    
    return out;

}


Image convolution_valid(Image& img, Matrix& kernel){
    int kh=kernel.size();
    int kw=kernel[0].size();

    Image out=zeros_like(img);
   
   

    for(int c=0; c<out.channels; c++){
        for(int x=0;x<img.h;x++){
            for(int y=0; y<img.w; y++){
                u8 val=0;
                for(int i=x-kh/2; i<=x+kh/2 ; i++){
                    for(int j=y-kw/2; j<=y+kw/2  ;j++){
                        

                        if((i>=0 && i<img.h) &&(j>=0 && j<img.w)){
                        
                            val+=kernel[i-(x-kh/2)][j-(y-kw/2)]*img.data[(i*img.w+j)*img.channels+c];
                        
                        }
                    }

                    out.data[(x*out.w+y)*out.channels+c]=val;

                }

          
        }
    }


    }
    return out;



}


Image Conv2d(Image& input,Matrix kernel,  bool padding=true){
        Image result;
        
        switch (padding==true)
        {
        case (1): 
        {

            printf("Same\n");
            Image _int=cv::convolution_full(input, kernel);
            result.malloc(_int);

            

            break;
        }
        case(0):
        {
            printf("Valid\n");
            Image _int=cv::convolution_full(input, kernel);
            result.malloc(_int);


            break;
        }
        default :{
            printf("Not Implemented");
            
            break;
        }

        }


        return result;
}


}



#endif
