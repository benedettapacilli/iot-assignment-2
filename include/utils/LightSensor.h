#pragma once
#include "Arduino.h"

class LightSensor
{
private:
    int pin;

public:
    LightSensor();
    LightSensor(int pin);
    int getLightLevel();
};