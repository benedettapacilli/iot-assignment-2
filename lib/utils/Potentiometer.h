#pragma once
#include "Arduino.h"

class Potentiometer
{
private:
    int pin;

public:
    Potentiometer();
    Potentiometer(int pin);
    int read();
};