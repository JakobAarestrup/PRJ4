#include "handDetector.h"

handDetector::handDetector()
{
    state_ = 0;
}

void handDetector::detectHand()
{
    wiringPiSetup(); //initialisering
    pinMode(GPIO, INPUT);
    wiringPiISR(GPIO, INT_EDGE_FALLING, &handle); //Skal trigge, når GPIO 7 får et falling edge signal
    while(state_ != 1) //Venter herinde indtil en hånd er detekteret
    {
    }
}

void handDetector::handle()
{
    state_ = 1;
}