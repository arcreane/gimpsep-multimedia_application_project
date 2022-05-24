//
//  main.cpp
//  Projet_Multimedia
//
//  Created by Christopher  on 23/05/2022.
//

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat src, erosion_dst, dilation_dst;

//Initialisation of all the variables
int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 32;

void Erosion( int, void* );
void Dilation( int, void* );

int main( int argc, char** argv )
{
  //CommandLineParser parser( argc, argv, "{@input | LinuxLogo.jpg | input image}" );
  //src = imread( parser.get<String>( "@input" ), IMREAD_COLOR );

  //Read the image
  src = imread("/Users/christopher/Downloads/eco.jpg");
    
  //If there is no image or we cannot open the image
  if( src.empty() )
  {
    cout << "Could not open or find the image!\n" << endl;
    cout << "Usage: " << argv[0] << " <Input image>" << endl;
    return -1;
  }
    
  //Windows creation
  namedWindow( "Erosion Demo", WINDOW_AUTOSIZE );
  namedWindow( "Dilation Demo", WINDOW_AUTOSIZE );
  moveWindow( "Dilation Demo", src.cols, 0 );
    
  //Trackbars creation
  //Erosion trackbar
  createTrackbar( "Erosion type:", "Erosion Demo",
          &erosion_elem, max_elem,
          Erosion );
  //Size erosion trackbar
  createTrackbar( "Erosion size:", "Erosion Demo",
          &erosion_size, max_kernel_size,
          Erosion );
  //Type dilatation trackbar
  createTrackbar( "Dilatation type:", "Dilation Demo",
          &dilation_elem, max_elem,
          Dilation );
  //Size dilation trackbar
  createTrackbar( "Dilation size:", "Dilation Demo",
          &dilation_size, max_kernel_size,
          Dilation );
  Erosion( 0, 0 );
  Dilation( 0, 0 );
  waitKey(0);
  return 0;
}

//Erosion function
void Erosion( int, void* )
{
  //Erosion type initialisation
  int erosion_type = 0;
  //Erosion type selection
  if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
  else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
  else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }
  /*Kernel used for the erosion
   We used getStructuringElement to structure the shape of the kernel
  */
  Mat element = getStructuringElement( erosion_type,
                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                       Point( erosion_size, erosion_size ) );
  //Use cv::erode and show the result
  erode( src, erosion_dst, element );
  imshow( "Erosion Demo", erosion_dst );
}

//Dilatation function
void Dilation( int, void* )
{
  //Dilatation type initialisation
  int dilation_type = 0;
  //Dilatation type selection
  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
  else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
  else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }
  /*Kernel used for the dilatation
  We used getStructuringElement to structure the shape of the kernel
  */
  Mat element = getStructuringElement( dilation_type,
                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                       Point( dilation_size, dilation_size ) );
  //Use cv::dilate and show the result
  dilate( src, dilation_dst, element );
  imshow( "Dilation Demo", dilation_dst );
}

