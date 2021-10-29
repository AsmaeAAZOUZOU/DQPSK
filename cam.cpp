#include "opencv2/opencv.hpp"
#include "iostream"
#include <unistd.h>
#include <string>
#include <cstdlib>

using namespace std;

int main(int, char**) {
    
    int num = atoi(getenv("NUM"));
    //cout << num << endl;
    // open the first webcam plugged in the computer
    cv::VideoCapture camera(0);
    //cv::VideoCapture camera2(2);
    if (!camera.isOpened()) {
	std::cerr << "ERROR: Could not open camera" << std::endl;
	return 1;
    }
    camera.set(CV_CAP_PROP_FRAME_WIDTH,1920);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT,1080);
    //camera2.set(CV_CAP_PROP_FRAME_WIDTH,1920);
    //camera2.set(CV_CAP_PROP_FRAME_HEIGHT,1080);
    

    // this will contain the image from the webcam
    cv::Mat frame;
	
    // capture the next frame from the webcam
    
    //if (num % 2 ==0)
	camera >> frame;
    //else
	//camera2 >> frame;
    if(frame.empty())
	{
	  std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
	}
    // Save the frame into a file
    imwrite(getenv("IMAGEH"), frame); // A JPG FILE IS BEING SAVED
    cv::resize(frame, frame, cv::Size(600,400));
    imwrite(getenv("IMAGE"), frame); // A JPG FILE IS BEING SAVED
    cout << "done" << endl;

    	    

    return 0;
}
