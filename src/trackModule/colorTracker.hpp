#pragma once
#include <opencv2/opencv.hpp>

using cv::VideoCapture;


class ColorTracker{
private:
    int cameraId;
    VideoCapture cap;
    int width;
    int height;
public:
    ColorTracker(int cameraId);
    ~ColorTracker();

    void showCameraStatus();
};