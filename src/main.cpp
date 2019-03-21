#include <iostream>
#include "trackModule/colorTracker.hpp"
#include <opencv2/opencv.hpp>

using cv::VideoCapture;


int main(){
	auto a = *new ColorTracker(0);

    a.showCameraStatus();


    return 0;
}
