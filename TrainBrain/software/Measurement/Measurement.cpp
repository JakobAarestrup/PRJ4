#include "Measurement.h"

Measurement::Measurement()
{
  mInfo       = new PIDM();
  mInfo->pi = pigpio_start(0, 0);
  pulse_width = 0;
  rise_tick   = 0;
  rpm = 0;

  gpioSetMode(mInfo->HALL, PI_INPUT);
  gpioSetPullUpDown(mInfo->HALL, PI_PUD_UP);
};

void *PIDMeasurement(void *arg)
{
  PIDM *mInfo = (PIDM *)arg;

  // Set up callback for PWM input
  callback(mInfo->pi, mInfo->HALL, EITHER_EDGE, MeasureCallback);
};

// Callback function for measuring PWM input
void MeasureCallback(int pi, unsigned HALL, unsigned level, uint32_t tick)
{
  if (level == 1) // rising edge
  { 
    rise_tick = tick;
  }
  else if (level == 0) // falling edge
  {                                 
    pulse_width = tick - rise_tick;
    rpm = (1/pulse_width)*60;
  }
};

uint32_t Measurement::getRPM()
{
  return rpm;
}

PIDM *Measurement::getInfo()
{
  return mInfo;
};