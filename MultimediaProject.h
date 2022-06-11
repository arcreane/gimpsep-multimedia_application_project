
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <filesystem>

using namespace std;
using namespace cv;
using std::filesystem::directory_iterator;

#ifndef GIMPSEP_MULTIMEDIA_APPLICATION_PROJECT_MULTIMEDIAPROJECT_H
#define GIMPSEP_MULTIMEDIA_APPLICATION_PROJECT_MULTIMEDIAPROJECT_H


class MultimediaProject {
    static inline Mat current_image, modified_image, dummy, gray_current_image, detected_edges;
    static inline int function_pointer;
    static inline double slider_value;
    static inline int trackbar_slider, secondary_slider;
    static inline String path;

    //Brightness related functions
    static void brightness_trackbar( int, void* );

    //Resizing related private functions
    static void resize_trackbar( int, void* );

    //Canny related private functions
    static void canny_trackbar(int, void*);

    //Erosion Dilatation private functions
    static void erosion_trackbar(int, void*);
    static void dilatation_trackbar(int, void*);

    //Global functions
    static void callback_main_menu(int event, int x, int y, int flags, void* userdata);
    static void position_windows();
    static void display_instructions();
    static void input_menu(const String& function_name);

public:
    static int initialize();
    static int draw_main_menu();
    static void brightness_process();
    static void canny_process();
    static void resize_process();
    static void erosion_dilatation_process();
    static int stitching_process();
};


#endif //GIMPSEP_MULTIMEDIA_APPLICATION_PROJECT_MULTIMEDIAPROJECT_H
