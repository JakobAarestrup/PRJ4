#include "handDetector.h"
#include <wiringPi.h>

handDetector::handDetector()
{
    state_ = 0;
}

void handDetector::detectHand()
{
    wiringPiSetup(); //InitieriSng
    pinMode(GPIO, INPUT);
    wiringPiISR(GPIO, INT_EDGE_FALLING, &handle); //Skal trigge, når GPIO 7 får et falling edge signal
    while(state_ != 1)
    {
    }
}

void handDetector::handle()
{
    state_ = 1;
}