#include <iostream>
#include <opencv2/opencv.hpp>

int main(){
    cv::Mat img = cv::imread("apple.jpg");
    cv::imshow("View",img);
    cv::waitKey();

    return 0;
    return 0;
}
