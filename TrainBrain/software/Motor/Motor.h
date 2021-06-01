#pragma once
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "PID.h"
#include "softPwm.h" //Bibliotek til at lave PWM signal
#include "wiringPi.h" //Bibliotek til GPIO opsaetning

//#define	PIFACE_BASE	200
#define forward	1 //PWM-pinc
#define backward 24
using namespace std;

void* updateSpeed();

class Motor
{
public:
    Motor(PID* p1);
    void startMotor(int direction);
    void stopMotor(int direction);
    void setDirection();
private:
    static void* updateSpeed(void* arg);
    int pwmValue_ = 0;
    static int direction_;
    PID* p1_; // Objekt fra PID
    pthread_t motorThread;
};