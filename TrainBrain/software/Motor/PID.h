#pragma once
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "softPwm.h"

using namespace std;

struct PIDInfo
{
	bool calcFlag = true;

	float out = 0.0f;
    float setpoint; 
    float measurement;
	//Controller gains
	float Kp = 2.0f;
	float Ki = 0.5f;
	float Kd = 0.25f;

	//Derivative low-pass filter time constant
	float tau = 0.25f;

	//Output limits
	float limMin = -10.0f;
	float limMax = 10.0f;

	//Integrator limits
	float limMinInt = -5.0f;
	float limMaxInt = 5.0f;

	//Sample time (in seconds)
	float T = 0.01f;

	//Controller "memory"
	float integrator = 0.0f;
	float prevError = 0.0f;			//Required for integrator
	float differentiator = 0.0f;
	float prevMeasurement = 0.0f;	//Required for differentiator
};

void* PIDController_Update_thread(void* pInfo);

class PID
{
public:
	PID();
    void  PIDController_Init();
    //void PIDController_Update(float setpoint, float measurement);
    float getOut();
	void setMeasurement(float measurement);
	void setSetPoint(float setPoint);
	PIDInfo* getInfo();
private:
    PIDInfo pInfo;
};
