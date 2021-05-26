#include "QrCode.hpp"

using namespace cv;
using namespace std;


string QrCode_thread(void* arg)
{
  string *tableNo = (string*)arg;
  //Capture camera
  VideoCapture cap;
  // brug noget andet end 0, hvis default ikke skal bruges
  if (!cap.open(0))
  {
    cout << "Intet kamera fundet" << endl;
    return 0;
  }
  cap.set(CAP_PROP_FRAME_WIDTH,640);
  cap.set(CAP_PROP_FRAME_HEIGHT,480);
  cap.set(CAP_PROP_FPS,24);
  
  while(data_return != *tableNo)
  {
    Mat frame;
    cap >> frame;
    if( frame.empty() ) 
    {
      break; // end of video stream
      cout << "Fejl i kamera billede" << endl;
    }

    QRCodeDetector qrDecoder;

    //Aflæser frame for QR coder og decoder dem.
    string data = qrDecoder.detectAndDecode(frame);

    //udskriver hvilken data den har fundet
    if(data.length()>0)
    {
      cout << "Decoded Data : " << data << endl;
      int data_return = boost::lexical_cast<int>(data);
    }
    else
      cout << "QR Code not detected" << endl;
  }
  int QrFlag = 1;
  return data_return;
}

// meget vigitg at du compiler den sådan her:
// g++ QrCode.cpp -o QrCode `pkg-config --cflags --libs opencv`