#include "QrCode.hpp"

using namespace cv;
using namespace std;
using namespace zbar;

ImageScanner scanner;
raspicam::RaspiCam_Cv Camera;

string QrCode_thread(void *arg) // Funktion til at koere QR scanner
{
  string *tableNo = (string *)arg;
  string data;
  // Configurer scanner til at have rigtige opløsning og fps, samt indstillinger
  // for Zbars Qr scanner
  scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 0);
  scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);
  Camera.set(CAP_PROP_FORMAT, CV_8UC1);
  Camera.set(CAP_PROP_FRAME_HEIGHT, 480);
  Camera.set(CAP_PROP_FRAME_WIDTH, 640);
  Camera.set(CAP_PROP_FPS, 30);
  // opretter forbindelse til kamera
  Camera.open();

  for (;;)
  {
    // Sætter billederne fra kameraet ind i en variable
    Mat frame;
    Camera.grab();
    Camera.retrieve(frame);
    // Tjekker om der er lagt data ind i variablen fra billederne
    if( frame.empty() ) 
    {
      break; // end of video stream
      cout << "Fejl i kamera billede" << endl;
    }
    
    // laver billedet om til grå farve
    Image image(frame.cols, frame.rows, "Y800", (uchar *)frame.data,  frame.cols *frame.rows);
    
    // scanner billedet efter QR koder
    int n = scanner.scan(image);

    // Dekoder fundne QR koder
    for(Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
    {
      data = symbol->get_data();
    }

    // tjekker Qr koden faktisk indeholdte det ønskede data
    if(data == *tableNo)
    {
      break;
    }

    //// Viser video fra kameraet på GUI, skal ikke tilføjes medmindre koden skal debugges
    imshow("this is you, smile! :)", frame);

    //// Stopper med at optage ved at trykke ESC, skal også kun tilføjes ved debugging
    if( waitKey(10) == 27 ) break; 
  }
  // Frigiver kameraet sådan at det ikke fejler ved næste søgning
  Camera.release();

  return data;
}

// meget vigtigt at du compiler den sådan her:
// g++ main.cpp QrCode.cpp -o test `pkg-config --cflags --libs opencv zbar` -I/usr/local/include/ -lraspicam -lraspicam_c