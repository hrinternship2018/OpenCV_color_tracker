#include <iostream>
#include <opencv2/opencv.hpp>

int main(){
    cv::Mat img = cv::imread("../res/apple.jpg");
    cv::imshow("View",img);
    cv::waitKey();

    return 0;
}
