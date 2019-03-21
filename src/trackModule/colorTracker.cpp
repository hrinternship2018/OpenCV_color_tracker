#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "colorTracker.hpp"

using std::cout;
using std::endl;
using cv::VideoCapture;

ColorTracker::ColorTracker(int cameraId){
    this->cameraId = cameraId;
    this->cap = *new VideoCapture(cameraId);
	if (this->cap.isOpened()) {
		cout << "successed to allocate camera: " << this->cameraId << endl;
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
		cout << "successed to release camera: " << this->cameraId << endl;
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



