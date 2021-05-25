Før denne kode virker, skal du downloade et biblotek med: 

1. Sudo apt-get install libboost1.67-all

Udover dette skal "opencv_all" mappen ligge sammen med koden, når man compiler skal man bruge ekstra parameter:

`pkg-config --cflags --libs opencv`

En fuld compilering af koden ville se sådan her ud:

g++ main.cpp QrCode.cpp -o QrCode `pkg-config --cflags --libs opencv`

En sidste ting er at QrCoden SKAL kun indeholde tal, ellers fejler koden. Dette skyldes at vi laver dataen i Qr-koden om til integer og returnere det.  