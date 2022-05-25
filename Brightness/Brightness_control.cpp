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
   
   
	for( int x = 0; x < image.cols ; x++ ) {//For each column
		for(int y = 0; y < image.rows ; y++) { //For each row
			for( int c = 0; c < 3; c++ ) {//For each color (GBR)
				new_image.at<Vec3b>(y,x)[c] =
					saturate_cast<uchar>( image.at<Vec3b>(y,x)[c] + alpha ); //New value is assigned to the new_image matrix
			}
		}
	}
	imshow("Output", new_image);//Display the output in a window
}

int main( int argc, char** argv )
{
    /*< Simple contrast control */
    /*< Simple brightness control */
    //reading the image and creating a new image matrix
	image = imread("eco.jpg", IMREAD_COLOR);
    
	if(!image.data )//If no image
	{
		printf( " No image data \n " );
		return 1;
	}
	
	new_image =	Mat::zeros(image.size(), image.type());//Create an empty new_image Matrix
    
    //create windows
    namedWindow("Source", WINDOW_AUTOSIZE);
	namedWindow("Output", WINDOW_AUTOSIZE);
	
	
    //show original and new image
	imshow("Source", image);
	 
	//Create slider
	alpha_slider = 0;
	
	//Create a Trackbar Name
	char TrackbarName[50];
	//Assign Trackbar Name as well as Max Value
	sprintf( TrackbarName, "Brightness Control", 255 );
	//Create the trackbar, assign it to a window, its slider, max value and on_change function
	createTrackbar( TrackbarName, "Output", &alpha_slider, 255, on_trackbar );
	//Set trackbar min value
	setTrackbarMin(	TrackbarName, "Output", -255);
	//Execute on_change function to initialize
	on_trackbar(alpha_slider, 0 );
    
    waitKey();
    return 0;
}
