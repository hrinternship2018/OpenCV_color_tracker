#pragma once
#include <iostream>
#include <exception>
#include <opencv2/opencv.hpp>
#include "trackModule/colorTracker.hpp"

using std::cout;
using std::endl;
using std::exception;

void exceptionHandler(exception& e){
    cout << endl << "called exception = " << typeid(e).name() << endl;
    cout << "what() result: \"" <<e.what() << "\""<< endl;
    return;
}



int main() try{
    
    /*auto a = *new ColorTracker(0);

    a.showCameraStatus();
    a.showCaptureImage();

    auto img = a.getCaptureImage();

    a.imshow(img);

    return 0;*/

    auto img = cv::imread("../res/apple.jpg");
    //auto mask = ColorTracker::getHue(img);
    auto mask = ColorTracker::getColorMask(img,rangeRed);

    auto a = ColorTracker::getContours(mask);

    cv::drawContours(img,a,-1,cv::Scalar(255,255,255));

    ColorTracker::imshow(img);

    

    //cout << rangeRed.high << endl;

} catch(exception& e){

    exceptionHandler(e);
    return 0;
}
