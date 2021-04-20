#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;

int main( )
{
    namedWindow("HSV Tester");   // Create a GUI window called photo

    int lowH = 0, highH = 179, lowS = 0, highS = 255, lowV = 0, highV = 255;    // Initialise some variables for HSV limits

    createTrackbar("Low Hue", "HSV Tester", &lowH, 179, NULL);      // Create trackbar controls for each HSV limit
    createTrackbar("High Hue", "HSV Tester", &highH, 179, NULL);

    createTrackbar("Low Sat", "HSV Tester", &lowS, 255, NULL);
    createTrackbar("High Sat", "HSV Tester", &highS, 255, NULL);

    createTrackbar("Low Value", "HSV Tester", &lowV, 255, NULL);
    createTrackbar("High Value", "HSV Tester", &highV, 255, NULL);

    Mat frame = imread("OpenCV_Logo.png"); // Open an image file and store in a new matrix variable

    while(1)    // Main loop to perform image processing
    {
        lowH = getTrackbarPos("Low Hue", "HSV Tester");        // Update the variables with the trackbar setting
        highH = getTrackbarPos("High Hue", "HSV Tester");
        lowS = getTrackbarPos("Low Sat", "HSV Tester");
        highS = getTrackbarPos("High Sat", "HSV Tester");
        lowV = getTrackbarPos("Low Value", "HSV Tester");
        highV = getTrackbarPos("High Value", "HSV Tester");

        Mat frameHSV;       // Convert the frame to HSV and apply the limits
        cvtColor(frame, frameHSV, COLOR_BGR2HSV);
        inRange(frameHSV, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), frameHSV);

        Mat comparison;     // Join the two into a single image
        cvtColor(frameHSV, frameHSV, COLOR_GRAY2BGR);   // In range returns the equivalent of a grayscale image so we need to convert this before concatenation
        hconcat(frame, frameHSV, comparison);

        imshow("HSV Tester", comparison); //Display the image in the window

        int key = cv::waitKey(1);   // Wait 1ms for a keypress (required to update windows

        key = (key==255) ? -1 : key;    // Check if the esc key has been pressed
        if (key == 27)
            break;
	}

	destroyAllWindows();

	return 0;
}
