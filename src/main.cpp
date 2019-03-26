#include <iostream>
#include "trackModule/colorTracker.hpp"
#include <opencv2/opencv.hpp>

using std::cout;
using std::endl;

int main(){
    auto a = *new ColorTracker(0);

    a.showCameraStatus();
    a.showCaptureImage();

    auto img = a.getCaptureImage();
    a.imshow(img);


    return 0;
}
