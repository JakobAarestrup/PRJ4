#include "Motor.h"


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

  p1_->setMeasurement(2);
  pwmWrite(direction, p1_->getOut());
};

void Motor::stopMotor(int direction)
{
  pwmWrite(direction, pwmValue_);
};

void updateSpeed()
{

};