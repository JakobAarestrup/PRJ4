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

class Motor
{
public:
    Motor(PID* p1);
	void updateSpeed();
    void startMotor(int direction);
    void stopMotor(int direction);
    void setDirection();
private:
    int pwmValue_ = 0;
    int direction_ = 0;
    PID* p1_;
};