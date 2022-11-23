#pragma once
#include "Arduino.h"

class Pir
{
private:
    int pin;

public:
    Pir();
    Pir(int pin);
    bool detect();
};