#pragma once
#include <iostream>
#include <exception>
#include <vector>
#include <future>
#include <opencv2/opencv.hpp>
#include "trackModule/colorTracker.hpp"
#include "trackModule/cameraHandler.hpp"

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

    auto a = CameraHandler();


    while(true){
        auto r = a.getAngles();
        cout << r[0] << endl;
    }
    

    return 0;
    


} catch(exception& e){

    exceptionHandler(e);
    return 0;
}
