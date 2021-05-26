#pragma once
#include "pigpio-master/pigpio.h"
#include "pigpio-master/pigpiod_if2.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

static uint32_t rise_tick;   // Pulse rise time tick value
static uint32_t pulse_width; // Last measured pulse width (us)

struct PIDM
{
  const unsigned int HALL = 2;
  int pi;
};

void* PIDMeasurement(void* arg);
void MeasureCallback(int pi, unsigned HALL, unsigned level, uint32_t tick);

class Measurement
{
public:
  Measurement();
  uint32_t getPWM();
  PIDM *getInfo();
  PIDM *mInfo;
};