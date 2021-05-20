#include <iostream>
#include <stdio.h>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat src1 = imread("ShapeCounter.png");
    Mat src2 = src1;
    Mat blurred;//blurred grey scale
    Mat pinkImage;//grey scale
    Mat combined;//morphed
    Mat kernel = cv::getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
    Mat blank1 = Mat::zeros( src1.size(), CV_8UC3 );
    Mat blank2 = blank1;


    if(src1.empty()||src2.empty())
        {
            std::cout << "There is no image " <<  std::endl;
            return 1;
        }

    cvtColor(src1,pinkImage,COLOR_BGR2HSV);
    inRange(pinkImage, Scalar(130, 90, 90), Scalar(168, 255, 255), pinkImage);
    blur(pinkImage, blurred, Size(3,3), Point(-1,-1));


    morphologyEx(blurred, combined, MORPH_OPEN, kernel);
    vector< vector<Point> > contours; // Variable for list of contours
    vector<Vec4i> hierarchy; // Variable for image topology data
    findContours(combined, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE,Point(0, 0)); // Calculate the contours and store them
    vector< vector<Point> > approxedcontours(contours.size());

    for(int i = 0; i < int(contours.size()); i++) // Loop through the contours
    {
        float epsilon = 0.03*arcLength(contours[i],true);
        approxPolyDP(contours[i],approxedcontours[i], epsilon, true);
        drawContours( blank1, approxedcontours, (int)i, Scalar(255,0,0), 2, LINE_8, noArray(), 0, Point() );
        drawContours( blank2, contours, (int)i, Scalar(255,0,0), 2, LINE_8, noArray(), 0, Point() ); // Draw each in red
    }
        imshow("Approx contours", blank1);
        imshow("contours", blank2);
        int counter = contours.size()-2;
        cout << "There are " <<counter<< " shapes"  <<  endl;

    waitKey();
    destroyAllWindows();
    return 0;
}
