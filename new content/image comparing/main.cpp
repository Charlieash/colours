#include <stdio.h>
#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv_aee.cpp"

using namespace cv;
int main()
{
    //int lowH = 130, highH = 179, lowS = 0, highS = 255, lowV = 0, highV = 255;

    Mat imagea = imread("BlueCar.bmp");
    Mat imageb = imagea;


    //cvtColor(imagea, imagea, COLOR_GRAY2BGR);
    //cvtColor(imageb, imageb, COLOR_GRAY2BGR);

    float match = compareImages(imagea, imageb);
    std::cout << match;
}
