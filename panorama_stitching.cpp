#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <filesystem>

using namespace cv;
using namespace std;
using std::filesystem::directory_iterator;

Stitcher::Mode mode = Stitcher::PANORAMA;


int main() {
    string path;
    cout << "Entrez le chemin ou trouver les images" << endl;
    cin >> path;

    vector<string> listLinkImage;
    vector<Mat3b> listImage;
    int rows = 0;
    int cols = 0;
    int newColumn = 0;
    int lastColumn = 0;

    Mat result;

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
    Stitcher::Status status = stitcher->stitch(listImage, res);

    if (status != Stitcher::OK)
    {
        cout << "Can't stitch images\n";
        for (auto const &i : listImage) {
            newColumn += i.cols;
            i.copyTo(res(Rect(lastColumn, 0, i.cols, i.rows)));
            lastColumn = newColumn;
        }
        imshow("Panorama, without border detection", res);
        waitKey();
        return -1;
    }


    imshow("Panorama", res);
    waitKey();

    return 0;
}