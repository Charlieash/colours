#include <stdio.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "opencv_aee.hpp"
#include "opencv_aee.cpp"
#include "main.hpp"

using namespace cv;
using namespace std;
Mat src;
Mat src_gray;
int thresh = 200;
int max_thresh = 255;
RNG rng(12345);
void thresh_callback(int, void* );
int main( int argc, char** argv )
{

    String imageName("ShapeCounter.png"); // by default
    if (argc > 1)
    {
        imageName = argv[1];
    }
    src = imread(imageName, IMREAD_COLOR);
    if (src.empty())
    {
        cerr << "No image supplied ..." << endl;
        return -1;
    }
    cvtColor( src, src_gray, COLOR_BGR2GRAY );

    blur( src_gray, src_gray, Size(3,3) );
    const char* source_window = "Source";
    namedWindow( source_window, WINDOW_AUTOSIZE );
    imshow( source_window, src );
    thresh_callback( 0, 0 );
    waitKey(0);
    return(0);
}
void thresh_callback(int, void* )
{
    Mat canny_output;
    int smallestX = 1000000000, smallestY = 100000000;
    int largestY = 0, largestX =0;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Canny( src_gray, canny_output, thresh, thresh*2, 5 );
    findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    std::vector< std::vector<cv::Point> > approxedcontours(contours.size()); // Array
    int a;
    for( size_t i = 0; i< approxedcontours.size(); i++ )
    {
        Scalar color = 255;
        a = (int)i;//test
        drawContours( drawing, contours, (int)i, color, 2, 8, hierarchy, 0, Point() );
    }


    namedWindow( "Contours", WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
    std:cout<< (int)a;
}


