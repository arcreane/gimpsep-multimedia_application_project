#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "Resize_control.h"

using namespace std;
using namespace cv;

Mat source, new_image;
int scale_slider;
double scaling_factor;
Size dsize;


//On_change function for the scale trackbar
static void scale_on_trackbar( int, void* ){
   scaling_factor = (double) scale_slider/100;
   
   dsize = Size(0,0);
   resize(source, new_image, dsize, scaling_factor, scaling_factor, INTER_LINEAR);
  
   imshow("Output", new_image);
   
}

//Draw the instructions on how to use this Resize tool
static void draw_control_image(){
	Mat instructions(90, 425, CV_8UC3, cv::Scalar(0));
	
	String text_how_scale = "Press 'a' to start a scale resize";  
	String text_how_dimensional = "Press 'z' to enable a (x,y) resize";
	String text_how_quit =  "Press ESC to exit";
	
	Point point_scale = Point(0, 30);
	Point point_dimensional = Point(0, 55);
	Point point_quit = Point(0, 80);
	
	int font_type = FONT_HERSHEY_DUPLEX;
	double font_scale = 0.75;
	Scalar font_color = CV_RGB(255, 255, 255);
	int thickness = 1;
	
	putText(instructions,
			text_how_scale,
			point_scale, //top-left position of the text
            font_type, //Font type
            font_scale, //Font Size multiplier
            font_color, //font color
            thickness);
			
	putText(instructions,
			text_how_dimensional,
			point_dimensional, //top-left position of the text
            font_type, //Font type
            font_scale, //Font Size multiplier
            font_color, //font color
            thickness);

	putText(instructions,
			text_how_quit,
			point_quit, //top-left position of the text
            font_type, //Font type
            font_scale, //Font Size multiplier
            font_color, //font color
            thickness);
			
	imshow("Controls", instructions);		
}



//Scale Resize main function
static void create_scale_window(){
	waitKey(1); //To avoid issues with the original waitKey(0) in the main loop 
	cout << "Scaling Resize initialized" << endl ;
	namedWindow("Controls", WINDOW_AUTOSIZE); //Create a control panel Window named "Control"
	draw_control_image();
	char TrackbarScale[50]; //Create a trackbar name
	sprintf( TrackbarScale, "Scale Control (%%)", 200 ); //Assign a description to the trackbar, as well as a max of 200
	createTrackbar( TrackbarScale, "Controls", &scale_slider, 200, scale_on_trackbar ); //Create the actual trackbar on the Window "Control", the value is stored in the "scale_slider" variable, on change executes the function "scale on trackbar"
	setTrackbarMin( TrackbarScale, "Controls", 1); //Sets the trackbar's min value to 1 (A window with an image of size 0% would cause an error)
	setTrackbarPos( TrackbarScale, "Controls", 100); //Assigns the slider's initial position to 100
	
	imshow("Source", source);
	scale_on_trackbar(scale_slider, 0); //Executes the function for the first time
	position_windows();
	
}


//Sets the windows at their correct positions
static void position_windows(){
	moveWindow("Source",0,0);	
	moveWindow("Controls",500,0);
	moveWindow("Output",1000,0);
}



//Dimensional Resize main function
static void create_dimensional_window(){
	waitKey(1); //To avoid issues with the original waitKey(0) in the main loop 
	int x, y;
	cout << "Dimensional Resize initialized" << endl ;
	x = -1;
	y = -1;
	//Define a width between 1 and 1920 pixels
	while (x < 1.0 || x > 1920.0 ) {
		cout << "Select the width" << endl ;
		cin >> x;}
	//Define a length between 1 and 11080 pixels
	while (y < 1.0 || y > 1080.0 ) {
		cout << "Select the length" << endl ;
		cin >> y;}
	
	cout << "Displaying new image" << endl ;
	
	dsize = Size(round(x), round(y));

	//Create the resized image
	resize(source, new_image, dsize, 0, 0, INTER_LINEAR);

	//Display the source and output images in their corresponding windows
	imshow("Source", source);
	imshow("Output", new_image);
	draw_control_image();
	position_windows();
}

static int initialize(){
	// Read source image
	source = imread("D:\\Projets\\Multimedia\\gimpsep-multimedia_application_project\\Resize\\Happyfish.jpg", IMREAD_COLOR);
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
	//Initialize, and exit if initializing failed
	if (initialize()==1) {
		return 1;
	}
 
	while(1){
		//if ESC is pressed, exit program 
		if ( (char)27 == (char) waitKey(0) ) {
			cout << "Exiting..." << endl ;
			break;
		} else if ( (char)97 == (char) waitKey(0) ) {//if 'a' is pressed, launch the scale resize function
			destroyAllWindows();
			create_scale_window();
		} else if ( (char)122 == (char) waitKey(0) ) {//if 'z' is pressed, launch the dimensional resize function
			destroyAllWindows();
			create_dimensional_window();
		}
	}
}
