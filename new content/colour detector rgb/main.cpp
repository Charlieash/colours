/*
**********************************************
Tool to make it easier to find the HSV values needed to isolate a chosen colour.
The raw camera feed is shown along with the inRange result. Silders allow the HSV limits to be changed during runtime.
**********************************************
*/

// Include files for required libraries
#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <string>
#include <windows.h>

using namespace cv;

int main( )
{
    std::string colour = "ble";
    int i = 0, countBlue = 0, countGreen = 0, countRed = 0;
    int lowH = 0, highH = 179, lowS = 0, highS = 255, lowV = 0, highV = 255;    // Initialise some variables for HSV limits


    Mat frame = imread("GreenApple.bmp"); // Open an image file and store in a new matrix variable

    for(i = 0; i< 3; i++)
    {
        if(i == 0)
        {
            lowH = 90, highH = 179, lowS = 0, highS = 255, lowV = 0, highV = 255;
        }
        else if(i == 1)
        {
            lowH = 35, highH = 50, lowS = 0, highS = 255, lowV = 0, highV = 255;
        }
        else if(i==2)
        {
            lowH = 0, highH = 15, lowS = 0, highS = 255, lowV = 0, highV = 253;
        };
        Mat frameHSV;       // Convert the frame to HSV and apply the limits
        cvtColor(frame, frameHSV, COLOR_BGR2HSV);
        inRange(frameHSV, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), frameHSV);
        Mat comparison;     // Join the two into a single image
        cvtColor(frameHSV, frameHSV, COLOR_GRAY2BGR);   // In range returns the equivalent of a grayscale image so we need to convert this before concatenation
        hconcat(frame, frameHSV, comparison);
        for(int rownumber = 0; rownumber < frameHSV.rows; rownumber++)
        {
            uchar* p = frameHSV.ptr<uchar>(rownumber);
            for(int x = 0; x < frameHSV.cols; x++)
            {
                uchar pixel = p[x]; // read the data into pixel
                if(pixel == 255 && i ==0)
                {
                    countBlue = countBlue + 1;
                }
                else if(pixel == 255 && i ==1)
                {
                    countGreen = countGreen + 1;
                }
                else if(pixel == 255 && i ==2)
                {
                    countRed = countRed + 1;
                };
            }
        }
    }
    if(countRed > countGreen && countRed > countBlue)
    {
        std::cout << "Most Red";
    }
    else if(countGreen > countRed && countGreen > countBlue)
    {
        std::cout << "Most Green";
    }
    else if(countBlue > countRed && countBlue > countGreen)
    {
        std::cout << "Most Blue";
    }
    else
    {
        std::cout << "AAAAAAAAAAAAAAA";
    };


}




