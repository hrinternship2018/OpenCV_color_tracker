#pragma once
#include <iostream>
#include <exception>
#include <vector>
#include <opencv2/opencv.hpp>
#include "trackModule/colorTracker.hpp"

using std::cout;
using std::endl;
using std::exception;
using std::vector;

void exceptionHandler(exception& e){
    cout << endl << "called exception = " << typeid(e).name() << endl;
    cout << "what() result: \"" <<e.what() << "\""<< endl;
    return;
}



int main() try{
    
    auto a = *new ColorTracker(0);

    a.showCameraStatus();

    while(true){
        auto img = a.getCaptureImage();
        auto mask = a.getColorMask(img,rangeRed);
        auto contours = a.getConvexContours(mask);
        try{
            auto contour = a.getMaxAreaContour(contours);
            vector<vector<Point>> temp{contour};
            cv::drawContours(img,temp,0,cv::Scalar(255,255,255),5);
        } catch (exception& e){
            cout << e.what() << endl;
        }
        cv::imshow("a",img);
        auto ret = cv::waitKey(1);
        if(ret != -1){
            break;
        }

    }
    
    return 0;




    




} catch(exception& e){

    exceptionHandler(e);
    return 0;
}
