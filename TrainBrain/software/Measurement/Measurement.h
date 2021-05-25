#pragma once
#include <piggpio-master/pigpio.h>
#include <piggpio-master/pigpiod_if2.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

static void PIDMeasurement(int pi, unsigned user_gpio, unsigned level,
                           uint32_t tick);
class Measurement
{
public:
  Measurement();
  const unsigned int HALL = 24;

private:
  static uint32_t rise_tick;   // Pulse rise time tick value
  static uint32_t pulse_width; // Last measured pulse width (us)
};