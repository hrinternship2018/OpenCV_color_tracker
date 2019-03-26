#pragma once
#include <stdexcept>

//Exception class about camera
class CameraException: public std::runtime_error{
    public:
    CameraException(const char* message):runtime_error(message){}
    CameraException():runtime_error("CameraException"){}
    char* what();//return message
};