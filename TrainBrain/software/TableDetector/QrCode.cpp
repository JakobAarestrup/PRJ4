#include "QrCode.hpp"

using namespace cv;
using namespace std;
using namespace zbar;

ImageScanner scanner;

string QrCode_thread(void *arg)
{
  string *tableNo = (string *)arg;
  // Capture camera
  VideoCapture cap;
  // brug noget andet end 0, hvis default ikke skal bruges
  if (!cap.open(0))
  {
    cout << "Intet kamera fundet" << endl;
    return 0;
  }
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

  while (data != *tableNo)
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
  }

  // Frigiver kameraet sådan at det ikke fejler ved næste søgning
  Camera.release();

  return data;
}

// meget vigitg at du compiler den sådan her:
// g++ QrCode.cpp -o QrCode `pkg-config --cflags --libs opencv`