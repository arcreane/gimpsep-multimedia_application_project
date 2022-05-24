#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "Resize.h"

using namespace std;
using namespace cv;

Mat source, new_image;
int scale_slider;
double scaling_factor;
Size dsize;



static void scale_on_trackbar( int, void* ){
   scaling_factor = (double) scale_slider/100;
   
   dsize = Size(0,0);
   resize(source, new_image, dsize, scaling_factor, scaling_factor, INTER_LINEAR),
  
   imshow("Output", new_image);
}

static void create_scale_window(){
	waitKey(1); //To avoid issues with the original waitKey(0) in the main loop 
	cout << "Scaling Resize initialized" << endl ;
	namedWindow("Controls", WINDOW_NORMAL); //Create a control panel Window named "Control"
	char TrackbarScale[50]; //Create a trackbar name
	sprintf( TrackbarScale, "Scale Control (%%)", 200 ); //Assign a description to the trackbar, as well as a max of 200
	createTrackbar( TrackbarScale, "Controls", &scale_slider, 200, scale_on_trackbar ); //Create the actual trackbar on the Window "Control", the value is stored in the "scale_slider" variable, on change executes the function "scale on trackbar"
	setTrackbarMin( TrackbarScale, "Controls", 1); //Sets the trackbar's min value to 1 (A window with an image of size 0% would cause an error)
	setTrackbarPos( TrackbarScale, "Controls", 100); //Assigns the slider's initial position to 100
	scale_on_trackbar(scale_slider, 0); //Executes the function for the first time
}

static void create_dimensional_window(){
	waitKey(1); //To avoid issues with the original waitKey(0) in the main loop 
	int x, y;
	cout << "Dimensional Resize initialized" << endl ;
	x = -1;
	y = -1;
	while (x < 1.0 || x > 1920.0 ) {
		cout << "Select the width" << endl ;
		cin >> x;}
	while (y < 1.0 || y > 1080.0 ) {
		cout << "Select the length" << endl ;
		cin >> y;}

dsize = Size(round(x), round(y));
resize(source, new_image, dsize, 0, 0, INTER_LINEAR);
imshow("Source", source);
imshow("Output", new_image);
}

static int initialize(){
	// Read source image
source = imread("Happyfish.jpg", IMREAD_COLOR);
 if(!source.data )
 {
   printf( " No image data \n " );
   return 1;
 }

// Scaling factors
dsize = Size(0,0);
scale_slider = 0;


//Display windows and show for both images
 namedWindow("Source", WINDOW_AUTOSIZE);
 imshow("Source", source);
 namedWindow("Output", WINDOW_AUTOSIZE);
 	
 create_scale_window();	
 return 0;
}

int main(void)
{
 if (initialize()==1) {return 1;};
 
 while(1){
	if ( (char)27 == (char) waitKey(0) ) {//if ESC is pressed 
		break;}
	else if ( (char)97 == (char) waitKey(0) ) {//if 'a' is pressed
		destroyAllWindows();
		create_scale_window();
		}
	else if ( (char)122 == (char) waitKey(0) ) {//if 'z' is pressed
		destroyAllWindows();
		create_dimensional_window();
		}
 }
}
