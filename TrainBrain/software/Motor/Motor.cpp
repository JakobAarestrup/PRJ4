#include "Motor.h"
#include <signal.h>
#include <pthread.h>

void *Motor::updateSpeed(void *arg)
{
  PID *p1 = (PID *)arg;
  for (;;)
  {
    pwmWrite(direction_, (p1->getOut())*1024);
    usleep(10000);
  }
};

Motor::Motor(PID *p1)
{
  wiringPiSetup();
  pinMode(forward, PWM_OUTPUT);
  pinMode(backward, PWM_OUTPUT);
  p1_ = p1;
};

void Motor::startMotor(int direction)
{
  p1_->PIDController_Init();
  pthread_create(&motorThread, NULL, updateSpeed, (void *)NULL);
};

void Motor::stopMotor(int direction) 
{ 
  pthread_kill(motorThread, 0);
  pwmWrite(direction, pwmValue_);
};