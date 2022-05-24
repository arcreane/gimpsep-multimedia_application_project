#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int alpha_slider;
double alpha;
Mat image;
Mat new_image;

static void on_trackbar( int, void* )
{
   alpha = (double) alpha_slider;
   
   
    for( int x = 0; x < image.cols ; x++ ) {
        for(int y = 0; y < image.rows ; y++) { 
            for( int c = 0; c < 3; c++ ) {
                new_image.at<Vec3b>(y,x)[c] =
                  saturate_cast<uchar>( image.at<Vec3b>(y,x)[c] + alpha );
				  
           }
        }
    }
   imshow("DisplayTwo", new_image);
}

int main( int argc, char** argv )
{
                           /*< Simple contrast control */
                                     /*< Simple brightness control */
    //reading the image and creating a new image matrix
	image = imread("eco.jpg", IMREAD_COLOR);
    
	 if(!image.data )
	{
   printf( " No image data \n " );
   return 1;
	}
	
	new_image =	Mat::zeros(image.size(), image.type());
    
    //create windows
    namedWindow("DisplayOne", WINDOW_AUTOSIZE);
	namedWindow("DisplayTwo", WINDOW_AUTOSIZE);
	
	
    //show original and new image
	imshow("DisplayOne", image);
	 
	 
	alpha_slider = 0;
	
	char TrackbarName[50];
   sprintf( TrackbarName, "Brightness Control", 255 );
   createTrackbar( TrackbarName, "DisplayTwo", &alpha_slider, 255, on_trackbar );
   setTrackbarMin(	TrackbarName, "DisplayTwo", -255);
   on_trackbar(alpha_slider, 0 );
    
    waitKey();
    return 0;
}
