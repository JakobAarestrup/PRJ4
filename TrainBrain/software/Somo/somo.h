#pragma once

class somo
{
public:
somo();
void initSomo();
void playSound();
void stopSound();
void closeSomo();
private:
int fd;
};