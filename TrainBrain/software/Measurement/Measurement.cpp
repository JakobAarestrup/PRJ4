#include "Measurement.h"

Measurement::Measurement()
{
  mInfo       = new PIDM(); //Measurement Objekt til at indeholde Measurement data
  mInfo->pi = pigpio_start(0, 0); //Forbinder til pigpio daemon
  pulse_width = 0;
  rise_tick   = 0;
  rpm = 0;

  gpioSetMode(mInfo->HALL, PI_INPUT); //Saetter Hall som input GPIO
};

void *PIDMeasurement(void *arg)
{
  PIDM *mInfo = (PIDM *)arg;

  // Opsaetning af callback til PWM input
  callback(mInfo->pi, mInfo->HALL, EITHER_EDGE, MeasureCallback);
};

// Callback funktion til at maale PWM input
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
// Returnerr RPM
uint32_t Measurement::getRPM()
{
  return rpm;
}
// Returnerer Measurement objektet
PIDM *Measurement::getInfo()
{
  return mInfo;
};