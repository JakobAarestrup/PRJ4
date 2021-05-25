#include "Motor.h"
#include "PID.h"
#include "TableDetector/software/QrCode.hpp"
#include <pthread.h>

PID *         p1        = new PID();
PIDInfo       p1Info    = PIDInfo();
Motor *       m1        = new Motor(p1);
QrCode        q1        = QrCode();

int main()
{

  // Initialization and prep for loop
  p1->PIDController_Init();
  s1->initSomo();

  // Thread for PID controller calculation
  pthread_create(
      PIDThread, NULL,
      PIDController_Update_thread, // Function der skal kører og udregne når et
                                   // flag bliver sat
      (void *)p1->getInfo()); // Parameter til funktionen (void*) som indeholder
                              // al data der skal gå mellem funktion og main


  // Thread for measurements for PID controller
pthread_create(PIDThread2, NULL, PIDMeasurement, (void *)PIDInfo->getMeasurement());

// Thread for QR detector
pthread_create(QrThread, NULL, QrCode_thread()); 


  for (;;)
  {
    programStateSwitch(state);
  }
}