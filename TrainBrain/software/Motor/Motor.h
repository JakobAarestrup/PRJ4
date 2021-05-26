#pragma once
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "PID.h"
#include "softPwm.h"
#include "wiringPi.h"

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
    PID* p1_;
    pthread_t motorThread;
};