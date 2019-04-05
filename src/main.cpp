#pragma once
#include <iostream>
#include <exception>
#include <vector>
#include <future>
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

    //async introduction
    //カメラ2台だと、並行処理しないとfpsがシビアなので追加
    std::future<cv::Point2d> f1= std::async( std::launch::async , [&]()-> cv::Point2d { return a.predict(rangeRed); });
    auto point = f1.get();

    cout << point << endl;
    
    

    return 0;
    


} catch(exception& e){

    exceptionHandler(e);
    return 0;
}
