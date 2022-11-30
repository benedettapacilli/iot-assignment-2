#include "LightSensor.h"

LightSensor::LightSensor()
{
}

LightSensor::LightSensor(int pin)
{
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

int LightSensor::getLightLevel()
{
    return analogRead(this->pin);
}