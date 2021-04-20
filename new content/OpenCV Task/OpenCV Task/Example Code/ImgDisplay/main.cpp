#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat image = imread("OpenCV_Logo.png");

    if (image.data == NULL)
    {
        cout << "No image found! Check path." << endl;
        return 1;   //ERROR
    }
    else
    {
        namedWindow("Logo", CV_WINDOW_AUTOSIZE);
        imshow("Logo", image);
        waitKey();//without this image won't be shown
        return 0;//OK
    }

}
