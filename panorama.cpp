#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <filesystem>
#include<list>

using namespace cv;
using namespace std;
using std::filesystem::directory_iterator;


int main() {
    string path = "/home/mollier/Téléchargements/panorama/";

    list<string> listLinkImage;
    list<Mat3b> listImage;
    int rows = 0;
    int cols;
    int newColumn = 0;
    int lastColumn;

    for (const auto & file : directory_iterator(path)) {listLinkImage.push_back(file.path());}

    for (auto const &i : listLinkImage) {listImage.push_back(imread(i));}

    for (auto const &i : listImage) {
        if (rows < i.rows) {
            rows = i.rows;
        }
        cols += i.cols;
    }

    Mat3b res(rows, cols, Vec3b(0,0,0));

    for (auto const &i : listImage) {
        newColumn += 0;
        i.copyTo(res(Rect(lastColumn, 0, i.cols, i.rows)));
        lastColumn = newColumn;
    }

    imshow("Panorama", res);
    waitKey();

    return 0;
}
