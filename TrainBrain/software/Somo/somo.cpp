#include "somo.h"
#include <iostream>         // til brug af cout
#include "wiringSerial.h"   // Bibliotek til serial funktioner
#include <termios.h>		// Bibliotek der bruges af wiringSerial.h
using namespace std;

void somo::initSomo()
{
    cout << "\ninitializing serial connection to SOMO\n";
    fd = serialOpen("/dev/ttyS0", 9600); // Aabner serial forbindelse til SOMO-II
}
void somo::closeSomo()
{
    cout << "closing serial connection to SOMO\n";
    serialClose(fd); // Lukker serial forbindelse til SOMO-II
}

void somo::playSound()
{
    cout << "Sending play command to SOMO\n";
    const char valStart1[] = {0x7E,0x0D,0x01}; // Start command, command code, feedback bit.
    const char valStart2[] = {0xFF,0xF3,0xEF}; // Checksum #1, checksum #2, end command.
    const char ZeroByte = 0x00;

    // Sender Play kommando til SOMO-II
    serialFlush(fd);
    serialPuts(fd,valStart1); // Foerste del af kommando bliver sendt
    serialPutchar(fd,ZeroByte); // Zero bytes bliver sendt
    serialPutchar(fd,ZeroByte); // Zero bytes bliver sendt
    serialPuts(fd,valStart2); // Anden del af kommando bliver sendt
}

void somo::stopSound()
{
    cout << "Sending stop command to SOMO\n";
    const char valStop1[] = {0x7E,0x16,0x01}; // Start command, command code, feedback bit.
    const char valStop2[] = {0xFF,0xEA,0xEF}; // Checksum #1, checksum #2, end command.
    const char ZeroByte = 0x00;

    serialPuts(fd,valStop1); // Foerste del af kommando bliver sendt
    serialPutchar(fd,ZeroByte); // Zero bytes bliver sendt
    serialPutchar(fd,ZeroByte); // Zero bytes bliver sendt
    serialPuts(fd,valStop2); // Anden del af kommando bliver sendt
}