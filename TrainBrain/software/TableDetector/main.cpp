#include "QrCode.hpp"
#include <iostream>

using namespace std;

int main()
{
    QrCode q1 = QrCode();
    int data = q1.capture_QR();
    cout << "Bord nr.: " << data << endl; 
    return 0;
}