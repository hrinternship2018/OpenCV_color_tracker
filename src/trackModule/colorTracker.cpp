#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "colorTracker.hpp"

using std::cout;
using std::endl;
using cv::VideoCapture;
using cv::Mat;


ColorTracker::ColorTracker(int cameraId){
    this->cameraId = cameraId;
    this->cap = *new VideoCapture(cameraId);
	if (this->cap.isOpened()) {
		cout << "succeeded to allocate camera: " << this->cameraId << endl;
        this->width = (int) this->cap.get(cv::CAP_PROP_FRAME_WIDTH);
        this->height = (int) this->cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	}
	else {
		cout << "failed to allocate camera: " << this->cameraId << endl;
        cout << "terminate program" << endl;
        this->cap.release();
		exit(1);
	}
}

ColorTracker::~ColorTracker(){
    if(!this->cap.isOpened()){
        return;
    }
    this->cap.release();
	if (!this->cap.isOpened()) {
		cout << "succeeded to release camera: " << this->cameraId << endl;
	}
	else {
		cout << "failed to release camera: " << this->cameraId << endl;
	}
    return;
}

void ColorTracker::showCameraStatus(){
    cout << "Width: " << this->cap.get(cv::CAP_PROP_FRAME_WIDTH) << endl;
    cout << "Height: " << this->cap.get(cv::CAP_PROP_FRAME_HEIGHT) << endl;
}

void ColorTracker::showCaptureImage(){
    Mat img;
    if(!this->cap.isOpened()){
        cout << "failed to open camera" << endl;
    }
    else{
        bool ret = this->cap.read(img);
        if(!ret){
            cout << "failed to get frame" << endl;
            return;
        }
        else{
            cv::imshow("showCaptureFrame",img);
            cv::waitKey(0);
            cv::destroyAllWindows();
        }
    }
}

Mat ColorTracker::getCaptureImage(){
    Mat img;
    if(!this->cap.isOpened()){
        cout << "failed to open camera" << endl;
    }
    else{
        bool ret = this->cap.read(img);
        if(!ret){
            cout << "failed to get frame" << endl;
        }
        else{
        }
    }
    return img;

}

void ColorTracker::imshow(Mat& img){
    cv::imshow("imshow",img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}


