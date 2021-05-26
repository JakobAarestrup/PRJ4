#pragma once
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <boost/lexical_cast.hpp>// for lexical_cast()

std::string QrCode_thread(void* arg);
class QrCode
{
public:
std::string capture_QR();
std::string QrCompare();
};