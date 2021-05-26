#pragma once
#include "wiringPi.h" //Inkluderes for at arbejde med GPIO på RPI

using namespace std;
#define GPIO 0 //Definér pin/pins

class handDetector
{
public:
    handDetector();
	void detectHand();
    static void handle();
private:
    static int state_;
};