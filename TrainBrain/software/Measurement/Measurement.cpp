#include "Measurement.h"

Measurement::Measurement()
{
  gpioSetMode(HALL, PI_INPUT);
  gpioSetPullUpDown(HALL, PI_PUD_UP);
};

// Callback function for measuring PWM input
void PIDMeasurement(int pi, unsigned user_gpio, unsigned level, uint32_t tick)
{
  rise_tick = 0;   // Pulse rise time tick value
  pulse_width = 0; // Last measured pulse width (us)
  if (level == 1)
  { // rising edge
    rise_tick = tick;
  }
  else if (level == 0)
  {                                 // falling edge
    pulse_width = tick - rise_tick; // TODO: Handle 72 min wrap-around
  }
};