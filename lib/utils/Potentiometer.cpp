#include "../include/utils/Potentiometer.h"

Potentiometer::Potentiometer() 
{
}

Potentiometer::Potentiometer(int pin) 
{
    this->pin = pin;
}

int Potentiometer::read()
{
    return analogRead(pin);
}