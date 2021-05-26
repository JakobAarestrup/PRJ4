#include "PID.h"

PID::PID() 
{
  pInfo = PIDInfo(); 
  // Clear controller variables
  pInfo.integrator      = 0.0f;
  pInfo.prevError       = 0.0f;
  pInfo.differentiator  = 0.0f;
  pInfo.prevMeasurement = 0.0f;
  pInfo.out             = 0.0f;
};

float PID::getOut() { return pInfo.out; };

PIDInfo *PID::getInfo() { return &pInfo; }

void *PIDController_Update_thread(void *param)
{
  // Get parameter
  PIDInfo *pInfo = (PIDInfo *)param;
  for (;;)
  {
    if (pInfo->calcFlag)
    {

      float error = pInfo->setpoint - pInfo->measurement;

      // Proportional
      float proportional = pInfo->Kp * error;

      // Integral
      pInfo->integrator = pInfo->integrator + 0.5f * pInfo->Ki * pInfo->T *
                                                  (error + pInfo->prevError);

      // Anti-wind-up via integrator clamping
      if (pInfo->integrator > pInfo->limMaxInt)
      {
        pInfo->integrator = pInfo->limMaxInt;
      }
      else if (pInfo->integrator < pInfo->limMinInt)
      {
        pInfo->integrator = pInfo->limMinInt;
      }

      // Derivative (band-limited differentiator)
      pInfo->differentiator =
          -(2.0f * pInfo->Kd *
                (pInfo->measurement -
                 pInfo->prevMeasurement) // Derivative on measurement, therefore
                                         // minus sign in front of equation!
            + (2.0f * pInfo->tau - pInfo->T) * pInfo->differentiator) /
          (2.0f * pInfo->tau + pInfo->T);

      // Compute output and apply limits
      pInfo->out = proportional + pInfo->integrator + pInfo->differentiator;

      if (pInfo->out > pInfo->limMax)
      {
        pInfo->out = pInfo->limMax;
      }
      else if (pInfo->out < pInfo->limMin)
      {
        pInfo->out = pInfo->limMin;
      }

      // Store error and measurement for later use
      pInfo->prevError       = error;
      pInfo->prevMeasurement = pInfo->measurement;
    }

  }

  return (void *)pInfo;
};

void PID::setMeasurement(float measurement)
{
  pInfo.measurement = measurement;
};
void PID::setSetPoint(float setPoint)
{
  pInfo.setpoint = setPoint;
};

/*void PID::PIDController_Update(float setpoint, float measurement)
{
        //Error Signal
        float error = setpoint - measurement;

        //Proportional
        float proportional = pInfo.Kp * error;

        //Integral
        pInfo.integrator = pInfo.integrator + 0.5f * pInfo.Ki * pInfo.T * (error
+ pInfo.prevError);

        //Anti-wind-up via integrator clamping
        if (pInfo.integrator > pInfo.limMaxInt)
        {
                pInfo.integrator = pInfo.limMaxInt;
        }
        else if (pInfo.integrator < pInfo.limMinInt)
        {
                pInfo.integrator = pInfo.limMinInt;
        }

        //Derivative (band-limited differentiator)
        pInfo.differentiator = -(2.0f * pInfo.Kd * (measurement -
pInfo.prevMeasurement) //Derivative on measurement, therefore minus sign in
front of equation!
                + (2.0f * pInfo.tau - pInfo.T) * pInfo.differentiator)/ (2.0f *
pInfo.tau + pInfo.T);

        //Compute output and apply limits
        pInfo.out = proportional + pInfo.integrator + pInfo.differentiator;

        if (pInfo.out > pInfo.limMax)
        {
                pInfo.out = pInfo.limMax;
        }
        else if (pInfo.out < pInfo.limMin)
        {
                pInfo.out = pInfo.limMin;
        }

        //Store error and measurement for later use
        pInfo.prevError = error;
        pInfo.prevMeasurement = measurement;
};*/