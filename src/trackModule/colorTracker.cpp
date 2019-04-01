#pragma once
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "colorTracker.hpp"
#include "cameraException.hpp"
#include "processingException.hpp"

#define WHERE "in " + string(__FILE__)+", at Line "+ to_string(__LINE__) +  ", " + string(__func__) + "(): "

using std::cout;
using std::endl;
using cv::VideoCapture;
using cv::Mat;
using cv::Point;
using std::exception;
using std::to_string;
using std::string;
using std::vector;


ColorTracker::ColorTracker(int cameraId) noexcept(false){
    this->cameraId = cameraId;
    this->cap = *new VideoCapture(cameraId);
	if (this->cap.isOpened()) {
		cout << "succeeded to allocate camera: " << this->cameraId << endl;
        this->width = (int) this->cap.get(cv::CAP_PROP_FRAME_WIDTH);
        this->height = (int) this->cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	}
	else {
		cout << "failed to allocate camera: " << this->cameraId << endl;
        this->cap.release();
		throw CameraException(WHERE + "failed to allocate camera: " + to_string(this->cameraId));
	}
}

ColorTracker::~ColorTracker() noexcept{
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

Mat ColorTracker::getCaptureImage() noexcept(false){
    Mat img;
    if(!this->cap.isOpened()){
        cout << "failed to open camera" << endl;
		throw CameraException(WHERE + "failed to open camera");
    }
    else{
        bool ret = this->cap.read(img);
        if(!ret){
            cout << "failed to get frame" << endl;
		    throw CameraException(WHERE + "failed to get frame");
        }
    }
    return img;

}

void ColorTracker::imshow(const Mat& img){
    cv::imshow("imshow",img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

Mat ColorTracker::getHSV(const Mat& imgBGR){
    if(imgBGR.channels()!=3){
        cout << "invalid input" << endl;
        throw ProcessingException(WHERE + "invalid input: passed image must have 3 channels");
    }

    Mat imgHSV;
    cv::cvtColor(imgBGR,imgHSV,cv::COLOR_BGR2HSV);

    return imgHSV;
}

Mat ColorTracker::getHue(const Mat& imgBGR){
    if(imgBGR.channels()!=3){
        cout << "invalid input" << endl;
        throw ProcessingException(WHERE + "invalid input: passed image must have 3 channels");
    }

    auto imgHSV = getHSV(imgBGR);

    auto imgHue = Mat( imgHSV.rows, imgHSV.cols, CV_8UC1);

    int collespond[] = {0,0};
    cv::mixChannels( &imgHSV, 1, &imgHue, 1, collespond, 1 );

    return imgHue;
}

Mat ColorTracker::getColorMask(const Mat& imgBGR,const colorRange& range){
    if(imgBGR.channels()!=3){
        cout << "invalid input" << endl;
        throw ProcessingException(WHERE + "invalid input: passed image must have 3 channels");
    }

    auto imgHSV = getHSV(imgBGR);

    vector<colorRange> rangeList;
    
    auto lowHue = range.low[0];
    auto highHue = range.high[0];

    if ((lowHue + 180) <= 255){
        if ((highHue + 180) <=255){
            colorRange temp = {cv::Scalar(range.low) , cv::Scalar(range.high)};
            temp.low[0] = lowHue + 180;
            temp.high[0] = highHue + 180;
            rangeList.push_back(temp);
        }
        else{
            colorRange temp = {cv::Scalar(range.low) , cv::Scalar(range.high)};
            temp.low[0] = lowHue + 180;
            temp.high[0] = 255;
            rangeList.push_back(temp);
        }
    }

    if ((highHue - 180) >= 0){
        if ((lowHue - 180) >=0){
            colorRange temp = {cv::Scalar(range.low) , cv::Scalar(range.high)};
            temp.low[0] = lowHue - 180;
            temp.high[0] = highHue - 180;
            rangeList.push_back(temp);
        }
        else{
            colorRange temp = {cv::Scalar(range.low) , cv::Scalar(range.high)};
            temp.low[0] = 0;
            temp.high[0] = highHue - 180;
            rangeList.push_back(temp);
        }
    }

    Mat mask(imgHSV.rows,imgHSV.cols,CV_8UC1);

    cv::inRange(imgHSV,range.low,range.high,mask);

    for(colorRange subRange:rangeList){
        Mat subMask(imgHSV.rows,imgHSV.cols,CV_8UC1);
        cv::inRange(imgHSV,subRange.low,subRange.high,subMask);
        cv::bitwise_or(mask,subMask,mask);
    }

    return mask;

}


vector<vector<Point>> ColorTracker::getContours(const Mat& mask) noexcept(false){
    vector<vector<Point>> contours;

    cv::findContours(mask,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_TC89_L1);
    
    return contours;
}