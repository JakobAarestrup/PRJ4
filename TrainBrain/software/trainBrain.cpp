#include "HandDetector/handDetector.h"
#include "Measurement/Measurement.h"
#include "Motor/Motor.h"
#include "Motor/PID.h"
#include "Somo/somo.h"
//#include "TableDetector/QrCode.hpp"
#include "BossBoundary/bossBoundary.h"
#include <pthread.h>

using namespace std;

enum programState
{
  startMotor,
  stopMotor,
  detectQRCode,
  detectHand,
  receiveOrder,
  deliverOrder
};

void programStateSwitch(programState &state);

pthread_t *PIDThread;
pthread_t *PIDMThread;
pthread_t *QrThread;

somo *  s1     = new somo();
PID *   p1     = new PID();
PIDInfo* pInfo =  new PIDInfo();
Motor * m1     = new Motor(p1);
// QrCode        q1        = QrCode();
handDetector *h1        = new handDetector();
Measurement * mInfo     = new Measurement();
string        tableNo   = "1";
int           direction = forward;
BossBoundary *boss      = new BossBoundary();

int main()
{
  programState state = receiveOrder;

  // Initialization and prep for loop
  s1->initSomo();

  // Thread for PID controller calculation
  pthread_create(
      PIDThread, NULL,
      PIDController_Update_thread, // Function der skal kører og udregne når et
                                   // flag bliver sat
      (void *)p1->getInfo()); // Parameter til funktionen (void*) som indeholder
                              // al data der skal gå mellem funktion og main

  // Thread for measurements for PID controller
  pthread_create(PIDMThread, NULL, PIDMeasurement, (void *)mInfo->getInfo());

  // Thread for QR detector
  // pthread_create(QrThread, NULL, QrCode_thread, (void*)boss.tableNo);
  for (;;)
  {
    programStateSwitch(state);
  }
}

void programStateSwitch(programState &state)
{
  switch (state)
  {
  case receiveOrder:
  {
    tableNo   = boss->receive();
    direction = forward;
    state     = startMotor;
  }
  break;

  case startMotor:
  {
    m1->startMotor(direction);
    pInfo->calcFlag = 1;
    state           = detectQRCode;
  }
  break;

  case stopMotor:
  {
    m1->stopMotor(direction);
    pInfo->calcFlag = 0;
    if (direction = forward) state = deliverOrder; else state = receiveOrder;
  }
  break;

  case detectQRCode:
  {
    //QrCode_thread();
    state = stopMotor;
  }
  break;

  case detectHand:
  {
    h1->detectHand();
    direction = backward;
    tableNo   = "0";
    state     = startMotor;
  }
  break;

  case deliverOrder:
  {
    s1->playSound(); // Afspiller lyd
    state = detectHand;
  }
  break;

  default:
  {
    // nothing
  }
  break;
  }
}