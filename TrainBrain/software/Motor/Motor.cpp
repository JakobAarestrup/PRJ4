#include "Motor.h"
#include <signal.h>
#include <pthread.h>

void *Motor::updateSpeed(void *arg)
{
  PID *p1 = (PID *)arg;
  for (;;)
  {
    pwmWrite(direction_, (p1->getOut())*1024); //Skriver PWM værdi til motor
    usleep(10000);
  }
};

Motor::Motor(PID *p1)
{
  wiringPiSetup(); // Opsaetning af wiringPi
  pinMode(forward, PWM_OUTPUT); //Saetter forward og backward som PWM output
  pinMode(backward, PWM_OUTPUT);
  p1_ = p1;
};

void Motor::startMotor(int direction)
{
  p1_->PIDController_Init(); // Resetter vaerdier i PID ved opstart
  pthread_create(&motorThread, NULL, updateSpeed, (void *)NULL); //Motor tråd der opdaterer hastighed for motor
};

void Motor::stopMotor(int direction) 
{ 
  pthread_kill(motorThread, 0); //Funktion til at stoppe motor tråden
  pwmWrite(direction, pwmValue_); //Funktion der stopper motor med PWM
};