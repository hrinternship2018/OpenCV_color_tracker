#pragma once
#include <opencv2/opencv.hpp>

using cv::VideoCapture;
using cv::Mat;


class ColorTracker{
private:
    int cameraId;
    VideoCapture cap;
    int width;
    int height;
public:
    ColorTracker(int cameraId) noexcept(false);// throw std::exception
    ~ColorTracker() noexcept;

    void showCameraStatus();
    void showCaptureImage();

    Mat getCaptureImage() noexcept(false);//throw std::exception

    static void imshow(Mat& img) noexcept(false);// throw std::exception

};