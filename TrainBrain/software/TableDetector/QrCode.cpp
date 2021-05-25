#include "QrCode.hpp"

using namespace cv;
using namespace std;


string QrCode_thread(void*);
{
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
  
  for(;;)
  {
    Mat frame;
    cap >> frame;
    if( frame.empty() ) 
    {
      break; // end of video stream
      cout << "Fejl i kamera billede" << endl;
    }
    // Viser video fra kameraet på GUI, skal ikke tilføjes medmindre koden skal debugges
    //imshow("this is you, smile! :)", frame);

    // stop med at optage ved at trykke ESC, skal også kun tilføjes ved debugging
    //if( waitKey(10) == 27 ) break; 

    //// kan tilføjes for at læse billeder, istedet for video
    // Read image
    // Mat inputImage;
    // if(argc>1)
    //   inputImage = imread(argv[1]);
    // else
    //   inputImage = imread("./qrcode.png");

    QRCodeDetector qrDecoder;

    Mat bbox, rectifiedImage;
    //Aflæser frame for QR coder og decoder dem.
    string data = qrDecoder.detectAndDecode(frame);

    //udskriver hvilken data den har fundet
    if(data.length()>0)
    {
      cout << "Decoded Data : " << data << endl;
      int data_return = boost::lexical_cast<int>(data);
      return data_return;
    }
    else
      cout << "QR Code not detected" << endl;
  }
  return 0;
}

/*string QrCode::capture_QR()
{
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
  
  for(;;)
  {
    Mat frame;
    cap >> frame;
    if( frame.empty() ) 
    {
      break; // end of video stream
      cout << "Fejl i kamera billede" << endl;
    }
    // Viser video fra kameraet på GUI, skal ikke tilføjes medmindre koden skal debugges
    //imshow("this is you, smile! :)", frame);

    // stop med at optage ved at trykke ESC, skal også kun tilføjes ved debugging
    //if( waitKey(10) == 27 ) break; 

    //// kan tilføjes for at læse billeder, istedet for video
    // Read image
    // Mat inputImage;
    // if(argc>1)
    //   inputImage = imread(argv[1]);
    // else
    //   inputImage = imread("./qrcode.png");

    QRCodeDetector qrDecoder;

    Mat bbox, rectifiedImage;
    //Aflæser frame for QR coder og decoder dem.
    string data = qrDecoder.detectAndDecode(frame);

    //udskriver hvilken data den har fundet
    if(data.length()>0)
    {
      cout << "Decoded Data : " << data << endl;
      int data_return = boost::lexical_cast<int>(data);
      return data_return;
    }
    else
      cout << "QR Code not detected" << endl;
  }
  return 0;
}*/

// meget vigitg at du compiler den sådan her:
// g++ QrCode.cpp -o QrCode `pkg-config --cflags --libs opencv`