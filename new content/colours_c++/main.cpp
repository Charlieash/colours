#include <iostream>
#include <stdio.h>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;

int main()
{
    namedWindow("HSV Tester");
    int lowH = 0, highH = 179, lowS = 0, highS = 255, lowV = 0, highV = 255;

    createTrackbar("Low Hue", "HSV Tester", &lowH,179,NULL);
    createTrackbar("High Hue", "HSV Tester", &highH,179,NULL);

    createTrackbar("Low Sat", "HSV Tester", &lowS,255,NULL);
    createTrackbar("High Sat", "HSV Tester", &highS,255,NULL);

    createTrackbar("Low Value", "HSV Tester", &lowV,255,NULL);
    createTrackbar("High Value", "HSV Tester", &highV,255,NULL);

    Mat frame = imread("OpenCV_Logo.png");

    while(1)
    {
        lowH = getTrackbarPos("Low Hue", "HSV Tester");
        highH = getTrackbarPos("High Hue", "HSV Tester");
        lowS = getTrackbarPos("Low Sat", "HSV Tester");
        highS = getTrackbarPos("High Sat", "HSV Tester");
        lowV = getTrackbarPos("Low Value", "HSV Tester");
        highV = getTrackbarPos("High Value", "HSV Tester");

        Mat frameHSV;
        cvtColor(frame, frameHSV, COLOUR_BGR2HSV);
        inRange(frameHSV, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), frameHSV);
        Mat comparison;
        cvtColor(frameHSV, frameHSV, COLOR_GRAY2BGR);
        hconcat(frame, frameHSV, comparison);
        imshow("HSV Tester", comparison);

        int key = cv::waitkey(1);
        key = (key ==255) ? 1 :key;
        if(key == 27)
            break;
    }
    destroyAllWindows();
    return 0;
}
