//
// Created by yanns on 10/06/2022.
//

#include "MultimediaProject.h"

//General Functions

int MultimediaProject::initialize() {
    String stitching_query;
    do {
        cout << "Start by stitching images (stitching is only available at the start of the edition) ? Yes / No" << endl;
        cin >> stitching_query;
    }while(stitching_query != "Yes" && stitching_query != "No");

    if (stitching_query == "No"){
        cout << "Insert the filepath to a specific image" << endl;
        cin >> path;

        dummy = imread(path);

        if(!dummy.data )//If no image
        {
            printf( " No image data \n " );
            return -1;
        }
        dummy.copyTo(current_image);
    } else if (stitching_query == "Yes"){
        cout << "Insert the filepath to a folder containing ONLY images to be stitched" << endl;
        cin >> path;
        if (stitching_process() == 0){
            cout << "Successful stitching!" << endl;
            dummy.copyTo(current_image);
        } else if (stitching_process() == -1){
            cout << "Failed to stitch images..." << endl;
            return -1;
        }
    }

    cout << "Initialization done! Please check the Main Menu window." << endl;
    return 0;
}

int MultimediaProject::draw_main_menu() {
    function_pointer = -1; //Reset the function pointer to -1
    slider_value = 0;
    trackbar_slider = 0;
    int main_menu_rows = 230;
    int main_menu_columns = 740;
    Mat main_menu_instructions(main_menu_rows, main_menu_columns, CV_8UC3, cv::Scalar(0));

    String instructions[] = {"Left click here to start a Brightness modification",
                             "Left click here to start a Resize modification",
                             "Left click here to start an Erosion / Dilatation modification",
                             "Left click here to start a Canny Edge modification",
                             "Press 's' to save the modified on your disk",
                             "Press 'c' to clear all changes, 'v' to save them",
                             "Press ESC to exit"
                             } ;

    int font_type = FONT_HERSHEY_DUPLEX;
    double font_scale = 0.75;
    Scalar font_color = CV_RGB(255, 255, 255);
    int thickness = 1;


    int gap = 30;

    for (int i = 1; i < 8; i++){
        putText(main_menu_instructions,
                instructions[i-1],
                Point(0, (gap * i)), //top-left position of the text
                font_type, //Font type
                font_scale, //Font Size multiplier
                font_color, //font color
                thickness);

        line(main_menu_instructions, Point(0, (((5/4)*gap))*i+5), Point(main_menu_columns, (((5/4)*gap))*i+5), Scalar(255, 255, 255),
             thickness, LINE_8);
    }


    namedWindow("Main Menu", WINDOW_AUTOSIZE);
    setMouseCallback("Main Menu", callback_main_menu, nullptr);
    imshow("Main Menu", main_menu_instructions);

    namedWindow("Current Image", WINDOW_AUTOSIZE);
    imshow("Current Image", current_image);

    position_windows();

    int k;
    while(true)
    {
        k= waitKey(20) & 0xFF;
        if(k== 99) { //if 'c' is pressed
            // Another way of cloning, clear all changes
            dummy.copyTo(current_image);
            cout << "All changes cleared!" << endl;
        } else if (k == 115){//if 's' is pressed, save image on disk
            imwrite("output.jpg", current_image);
            cout << "Saved the output image on disk!" << endl;
        } else if (k == 27){//if ESC is pressed
            function_pointer = 0; //Set function pointer to exit program
        }

        if(function_pointer != -1){//If function pointer has changed
            destroyAllWindows();
            return function_pointer; //return its value
        }
    }
}

void MultimediaProject::callback_main_menu(int event, int x, int y, int flags, void *userdata) {
    int gap = 30;
    if  ( event == EVENT_LBUTTONDOWN )
    {
        if (y <= ((((5/4)*gap))*1+5)){
            cout << "Brightness function selected" << endl;
            function_pointer = 1;
        } else if (y <= ((((5/4)*gap))*2+5)){
            cout << "Resize function selected" << endl;
            function_pointer = 2;
        } else if (y <= ((((5/4)*gap))*3+5)){
            cout << "Erosion / Dilatation function selected" << endl;
            function_pointer = 3;
        } else if (y <= ((((5/4)*gap))*4+5)){
            cout << "Canny Edge function selected" << endl;
            function_pointer = 4;
        }
    }
}

void MultimediaProject::input_menu(const String& function_name) {
    int k;
    while(true)
    {
        k= waitKey(20) & 0xFF;
        if(k== 99) { //if 'c' is pressed
            // Another way of cloning, clear all changes
            dummy.copyTo(current_image);
            cout << "All changes cleared!" << endl;
        } else if (k == 118){//if 'v'' is pressed
            modified_image.copyTo(current_image);
            cout << "Change applied!" << endl;
            imshow("Current Image", current_image);//Display the output in a window
        } else if (k == 115){//if 's' is pressed, save image on disk
            imwrite("output.jpg", current_image);
            cout << "Saved the output image on disk!" << endl;
        } else if (k == 27){//if ESC is pressed
            destroyAllWindows();
            String exit_message = "Exiting " + function_name + " function!";
            cout << exit_message << endl;
            break; //Set function pointer to exit program
        }

    }
}

void MultimediaProject::position_windows() {

    if (getWindowProperty("Main Menu",WND_PROP_VISIBLE) > 0){
        moveWindow("Main Menu",0,550);
    }
    if (getWindowProperty("Current Image",WND_PROP_VISIBLE) > 0){
        moveWindow("Current Image",0,0);
    }
    if (getWindowProperty("Output",WND_PROP_VISIBLE) > 0){
        moveWindow("Output",1000,0);
    }
    if (getWindowProperty("Instructions",WND_PROP_VISIBLE) > 0){
        moveWindow("Instructions",0,550);
    }

}


void MultimediaProject::display_instructions() {

    int instruction_rows = 230;
    int instruction_columns = 740;
    Mat instructionsCV(instruction_rows, instruction_columns, CV_8UC3, cv::Scalar(0));

    String instructions[] = {"Press 's' to save the modified on your disk",
                             "Press 'c' to clear all changes, 'v' to save them",
                             "Press ESC to exit"
    } ;

    int font_type = FONT_HERSHEY_DUPLEX;
    double font_scale = 0.75;
    Scalar font_color = CV_RGB(255, 255, 255);
    int thickness = 1;


    int gap = 30;

    for (int i = 1; i < 4; i++){
        putText(instructionsCV,
                instructions[i-1],
                Point(0, (gap * i)), //top-left position of the text
                font_type, //Font type
                font_scale, //Font Size multiplier
                font_color, //font color
                thickness);

        line(instructionsCV, Point(0, (((5/4)*gap))*i+5), Point(instruction_columns, (((5/4)*gap))*i+5), Scalar(255, 255, 255),
             thickness, LINE_8);
    }


    namedWindow("Instructions", WINDOW_AUTOSIZE);
    imshow("Instructions", instructionsCV);

}

//Stitching function

int MultimediaProject::stitching_process() {
    Stitcher::Mode mode = Stitcher::PANORAMA;

    vector<string> listLinkImage;
    vector<Mat3b> listImage;
    int rows = 0;
    int cols = 0;
    int newColumn = 0;
    int lastColumn = 0;

    for (auto const &file : directory_iterator(path)) {listLinkImage.push_back(file.path().string());}

    for (auto const &i : listLinkImage) {listImage.emplace_back(imread(i));}

    for (auto const &i : listImage) {
        if (rows < i.rows) {
            rows = i.rows;
        }
        cols += i.cols;
    }

    Mat3b res(rows, cols, Vec3b(0,0,0));

    Ptr<Stitcher> stitcher = Stitcher::create(mode);
    stitcher->setPanoConfidenceThresh(0.3);
    Stitcher::Status status = stitcher->stitch(listImage, res);

    if (status != Stitcher::OK)
    {
        cout << "Can't stitch images\n";
        for (auto const &i : listImage) {
            newColumn += i.cols;
            i.copyTo(res(Rect(lastColumn, 0, i.cols, i.rows)));
            lastColumn = newColumn;
        }
        res.copyTo(dummy, current_image);
        return -1;
    }

    res.copyTo(dummy, current_image);
    return 0;
}

//Brightness related functions

void MultimediaProject::brightness_trackbar(int, void *) {
    slider_value = (double) trackbar_slider;

    for( int x = 0; x < current_image.cols ; x++ ) {//For each column
        for(int y = 0; y < current_image.rows ; y++) { //For each row
            for( int c = 0; c < 3; c++ ) {//For each color (GBR)
                modified_image.at<Vec3b>(y,x)[c] =
                        saturate_cast<uchar>( current_image.at<Vec3b>(y,x)[c] + slider_value ); //New value is assigned to the new_image matrix
            }
        }
    }

    imshow("Current Image", current_image);//Display the output in a window
    imshow("Output", modified_image);//Display the output in a window
    position_windows();
}

void MultimediaProject::brightness_process() {
    namedWindow("Current Image", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);
    display_instructions();
    modified_image =	Mat::zeros(current_image.size(), current_image.type());//Create an empty new_image Matrix
    //Create a Trackbar Name
    char TrackbarName[50];
    //Assign Trackbar Name as well as Max Value
    sprintf( TrackbarName, "Brightness Control", 255 );
    //Create the trackbar, assign it to a window, its slider, max value and on_change function
    createTrackbar(TrackbarName, "Instructions", &trackbar_slider, 255, brightness_trackbar);
    //Set trackbar min value
    setTrackbarMin(	TrackbarName, "Instructions", -255);
    //Execute on_change function to initialize

    brightness_trackbar(trackbar_slider, nullptr);

    input_menu("Brightness");
}

//Resize related functions

void MultimediaProject::resize_trackbar(int, void *) {
    slider_value = (double) trackbar_slider/100;

    Size dsize = Size(0,0);
    resize(current_image, modified_image, dsize, slider_value, slider_value, INTER_LINEAR);
    imshow("Current Image", current_image);//Display the output in a window
    imshow("Output", modified_image);//Display the output in a window
    position_windows();
}

void MultimediaProject::resize_process() {
    modified_image =	Mat::zeros(current_image.size(), current_image.type());//Create an empty new_image Matrix
    Size dsize;

    String resize_query;
    do {
        cout << "Choose between scale and size editing : Scale / Size" << endl;
        cin >> resize_query;
    }while(resize_query != "Scale" && resize_query != "Size");

    namedWindow("Current Image", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);
    imshow("Current Image", current_image);
    display_instructions();

    if (resize_query == "Scale"){
        cout << "Scaling Resize initialized" << endl ;
        char TrackbarScale[50]; //Create a trackbar name
        sprintf( TrackbarScale, "Scale (%%)", 200 ); //Assign a description to the trackbar, as well as a max of 200
        createTrackbar( TrackbarScale, "Instructions", &trackbar_slider, 200, resize_trackbar); //Create the actual trackbar on the Window "Control", the value is stored in the "scale_slider" variable, on change executes the function "scale on trackbar"
        setTrackbarMin( TrackbarScale, "Instructions", 1); //Sets the trackbar's min value to 1 (A window with an image of size 0% would cause an error)
        setTrackbarPos( TrackbarScale, "Instructions", 100); //Assigns the slider's initial position to 100

        imshow("Current Image", current_image);
        resize_trackbar(trackbar_slider, nullptr); //Executes the function for the first time
    } else if (resize_query == "Size"){
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
        resize(current_image, modified_image, dsize, 0, 0, INTER_LINEAR);

        //Display the source and output images in their corresponding windows
        imshow("Output", modified_image);

    }

    position_windows();
    input_menu("Resize");
}

//Erosion Dilatation related functions

void MultimediaProject::erosion_trackbar(int, void *) {
//Erosion type initialisation
    int erosion_type = 0;
    //Erosion type selection
    if( secondary_slider == 0 ){ erosion_type = MORPH_RECT; }
    else if( secondary_slider == 1 ){ erosion_type = MORPH_CROSS; }
    else if( secondary_slider == 2) { erosion_type = MORPH_ELLIPSE; }
    /*Kernel used for the erosion
     We used getStructuringElement to structure the shape of the kernel
    */
    Mat element = getStructuringElement( erosion_type,
                                         Size( 2*trackbar_slider + 1, 2*trackbar_slider+1 ),
                                         Point( trackbar_slider, trackbar_slider ) );
    //Use cv::erode and show the result
    erode( current_image, modified_image, element );
    imshow("Current Image", current_image);//Display the output in a window
    imshow( "Output", modified_image );
    position_windows();
}

void MultimediaProject::dilatation_trackbar(int, void *) {
//Dilatation type initialisation
    int dilation_type = 0;
    //Dilatation type selection
    if( secondary_slider == 0 ){ dilation_type = MORPH_RECT; }
    else if( secondary_slider == 1 ){ dilation_type = MORPH_CROSS; }
    else if( secondary_slider == 2) { dilation_type = MORPH_ELLIPSE; }
    /*Kernel used for the dilatation
    We used getStructuringElement to structure the shape of the kernel
    */
    Mat element = getStructuringElement( dilation_type,
                                         Size( 2*trackbar_slider + 1, 2*trackbar_slider+1 ),
                                         Point( trackbar_slider, trackbar_slider ) );
    //Use cv::dilate and show the result
    dilate( current_image, modified_image, element );
    imshow("Current Image", current_image);//Display the output in a window
    imshow( "Output", modified_image);
    position_windows();
}

void MultimediaProject::erosion_dilatation_process() {
    int const max_elem = 2;
    int const max_kernel_size = 32;
    String ed_query;
    do {
        cout << "Choose between erosion and dilatation editing : Erosion / Dilatation" << endl;
        cin >> ed_query;
    }while(ed_query != "Erosion" && ed_query != "Dilatation");

    namedWindow("Current Image", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);
    display_instructions();

    if (ed_query == "Erosion"){
        //Erosion trackbar
        createTrackbar("Erosion type:", "Instructions",
                       &secondary_slider, max_elem,
                       erosion_trackbar);
        //Size erosion trackbar
        createTrackbar( "Erosion size:", "Instructions",
                        &trackbar_slider, max_kernel_size,
                        erosion_trackbar);
        erosion_trackbar( 0, nullptr );
    } else if (ed_query == "Dilatation") {
        //Type dilatation trackbar
        createTrackbar("Dilatation type:", "Instructions",
                       &secondary_slider, max_elem,
                       dilatation_trackbar );
        //Size dilation trackbar
        createTrackbar( "Dilation size:", "Instructions",
                        &trackbar_slider, max_kernel_size,
                        dilatation_trackbar );
        dilatation_trackbar(0, nullptr);
    }

    position_windows();
    input_menu("Erosion Dilatation");
}

//Canny Edge related functions

void MultimediaProject::canny_trackbar(int, void *) {
    const int ratio = 3;
    const int kernel_size = 3;
    slider_value = (double) trackbar_slider;
    //![reduce_noise]
    /// Reduce noise with a kernel 3x3
    blur(gray_current_image, detected_edges, Size(3, 3));
    //![reduce_noise]

    //![canny]
    /// Canny detector
    Canny(detected_edges, detected_edges, slider_value, slider_value * ratio, kernel_size);
    //![canny]

    /// Using Canny's output as a mask, we display our result
    //![fill]
    modified_image = Scalar::all(0);
    //![fill]

    //![copyto]
    current_image.copyTo(modified_image, detected_edges);
    //![copyto]

    //![display]
    imshow("Current Image", current_image);//Display the output in a window
    imshow("Output", modified_image);
    position_windows();
    //![display]

}

void MultimediaProject::canny_process() {
    const int max_lowThreshold = 100;


    modified_image.create(current_image.size(), current_image.type());

    cvtColor(current_image, gray_current_image, COLOR_BGR2GRAY);
    //![convert_to_gray]

    //![create_window]
    namedWindow("Current Image", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);
    display_instructions();
    //![create_window]

    //![create_trackbar]
    /// Create a Trackbar for user to enter threshold
    createTrackbar("Min Threshold:", "Instructions", &trackbar_slider, max_lowThreshold, canny_trackbar);
    //![create_trackbar]

    /// Show the image

    canny_trackbar(0, nullptr);

    position_windows();
    input_menu("Canny Edge");
}




int main( int argc, char** argv )
{
    MultimediaProject multimediaProject;
    if (multimediaProject.initialize() == -1){
        return -1;
    }


    while(true){
        int next_action_pointer = multimediaProject.draw_main_menu();

        switch (next_action_pointer) {
            case 0:
                cout << "Exiting Project..." << endl;
                return 0;
            case 1:
                cout << "Launching Brightness function" << endl;
                multimediaProject.brightness_process();
                break;
            case 2:
                cout << "Launching Resize function" << endl;
                multimediaProject.resize_process();
                break;
            case 3:
                cout << "Launching Erosion / Dilatation function" << endl;
                multimediaProject.erosion_dilatation_process();
                break;
            case 4:
                cout << "Launching Canny Edge function" << endl;
                multimediaProject.canny_process();
                break;
            default:
                return -1;//Throw an Error
        }
    }

}