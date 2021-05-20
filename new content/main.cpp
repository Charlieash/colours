#include <iostream>
#include <stdio.h>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

int main()
{


    Mat img = imread("ShapeCounter.png");
    Mat img2=imread("ShapeCounter.png");
    if(img.empty()||img2.empty())
        {
            std::cout << "Could not read the image " <<  std::endl;
            return 1;
        }

    Mat imgPink;//black and white
    Mat blurred;//blurred b&w
    Mat morphed;//after morph



    cvtColor(img,imgPink,COLOR_BGR2HSV);
    inRange(imgPink, Scalar(130, 90, 90), Scalar(168, 255, 255), imgPink);
    blur(imgPink, blurred, Size(3,3), Point(-1,-1));

    Mat kernel = cv::getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
    morphologyEx(blurred, morphed, MORPH_OPEN, kernel);
    vector< vector<Point> > contours; // Variable for list of contours
    vector<Vec4i> hierarchy; // Variable for image topology data
    findContours(morphed, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE,Point(0, 0)); // Calculate the contours and store them
    vector< vector<Point> > approxedcontours(contours.size());

    for(int i = 0; i < contours.size(); i++) // Loop through the contours
    {
        float epsilon = 0.03*arcLength(contours[i],true);
        approxPolyDP(contours[i],approxedcontours[i], epsilon, true);
        drawContours( img, approxedcontours, (int)i, Scalar(255,0,0), 2, LINE_8, noArray(), 0, Point() );
        drawContours( img2, contours, (int)i, Scalar(255,0,0), 2, LINE_8, noArray(), 0, Point() ); // Draw each in red
        cout << "Points of contour number"<<i<<":\n" <<approxedcontours[i]<<   endl;

        cout << "Number of points of contour number "<<i<<":" <<approxedcontours[i].size()<<  endl;
    }


        imshow("Approximated Contours", img);
        imshow("Not Approximated contours", img2);
        int counter = contours.size()-2;
        cout << "There are " <<counter<< " shapes!"  <<  endl;

    int key = waitKey();

    destroyAllWindows();
    return 0;
}





























