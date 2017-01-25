#ifndef DigitalGPIO
#define DigitalGPIO

#include <string>

int setSignal();
int pinMode(int gpionum, string mode);
int digitalRead(int gpionum);
int digitalWrite(int gpionum, string logicLevel);

#endif