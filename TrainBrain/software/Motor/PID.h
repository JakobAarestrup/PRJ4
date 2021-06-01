#pragma once
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "softPwm.h"
#include "../Measurement/Measurement.h"

using namespace std;

struct PIDInfo // Struct hvor der saettes vaerdier til udregning af PID
{
	bool calcFlag = true;
	Measurement* m;

	float out = 0.0f;
    float setpoint = 360; // Det oenskede RPM for motor
    float measurement; // Maalt RPM
	//Controller gains
	float Kp = 1.47f; // Vores udregnede Kp vaerdi
	float Ki = 12.8f; // Vores udregnede Ki vaerdi
	float Kd = 0.0425f; // Vores udregnede Kd vaerdi

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

	void setMeasurement(Measurement* MP) //Saetter m = Measurement pointer
	{
		m = MP;
	};
	float getMeasurement() //returnerer RPM fra m objekt
	{
		return m->getRPM();
	};
};

void* PIDController_Update_thread(void* pInfo);

class PID
{
public:
	PID(Measurement* MP);
    void  PIDController_Init();
    //void PIDController_Update(float setpoint, float measurement);
    float getOut();
	void setSetPoint(float setPoint);
	PIDInfo* getInfo();
private:
    PIDInfo pInfo;
};
