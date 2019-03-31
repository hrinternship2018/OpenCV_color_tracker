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
    
    auto a = *new ColorTracker(1);

    a.showCameraStatus();
    a.showCaptureImage();

    auto img = a.getCaptureImage();

    a.imshow(img);

    return 0;


} catch(exception& e){

    exceptionHandler(e);
    return 0;
}
