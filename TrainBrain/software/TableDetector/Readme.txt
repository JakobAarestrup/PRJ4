"opencv_all" og "zbar-0.10" mapperne skal ligge sammen med koden, når man compiler skal man bruge ekstra parameter:

`pkg-config --cflags --libs opencv zbar` -lraspicam -lraspicam_cv

En fuld compilering af koden ville se sådan her ud:

g++ main.cpp QrCode.cpp -o test `pkg-config --cflags --libs opencv zbar` -I/usr/local/include/ -lraspicam -lraspicam_cv