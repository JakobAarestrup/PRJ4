#include "HandDetector/handDetector.h"
#include "Measurement/Measurement.h"
#include "Motor/Motor.h"
#include "Motor/PID.h"
#include "TableDetector/QrCode.hpp"
#include "Somo/somo.h"
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

void programStateSwitch(programState pstate);

pthread_t *PIDThread;
pthread_t *PIDThread2;
pthread_t *QrThread;

int main()
{
  programState  state     = receiveOrder;
  somo *        s1        = new somo();
  PID *         p1        = new PID();
  PIDInfo       p1Info    = PIDInfo();
  Motor *       m1        = new Motor(p1);
  QrCode        q1        = QrCode();
  handDetector *h1        = new handDetector();
  int           direction = forward;

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
  pthread_create(PIDThread2, NULL, PIDMeasurement, (void *)p1);

  // Thread for QR detector
  pthread_create(QrThread, NULL, QrCode_thread, NULL);

  for (;;)
  {
    programStateSwitch(state);
  }
}

void programStateSwitch(programState state)
{
  switch (state)
  {
  case receiveOrder:
  {
    // receiveOrder();
    // direction = 0;
    state = startMotor;
  }
  break;

  case startMotor:
  {
    m1->startMotor(direction);
    // PIDThread.start(m1->updateSpeed());
    state = detectQRCode;
  }
  break;

  case stopMotor:
  {
    // m1->stopMotor();
    state = detectQRCode;
  }
  break;

  case detectQRCode:
  {
    /* detectQRCode(); 
    Skal sende parameter ind for at vide hvilken QR kode den skal stoppe ved*/
    if (direction == forward)
      state = stopMotor;
    else
      state = detectHand;
  }
  break;

  case detectHand:
  {
    h1->detectHand();
    direction = backward;
    state     = startMotor;
  }
  break;

  case deliverOrder:
  {

    s1->playSound(); // Afspiller lyd
    s1->closeSomo();
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