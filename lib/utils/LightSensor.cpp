#include "../../include/utils/LightSensor.h"

LightSensor::LightSensor()
{
}

LightSensor::LightSensor(int pin)
{
    this->pin = pin;
}

int LightSensor::getLightLevel()
{
    return analogRead(this->pin);
}