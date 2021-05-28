#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <raspicam/raspicam_cv.h>
#include <zbar.h>
#include <iostream>
#include <time.h>
#include <string>

#pragma once

std::string QrCode_thread(void *arg);