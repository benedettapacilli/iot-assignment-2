#pragma once
#include <Arduino.h>

class Led
{
private:
    int pin;
    int state;

public:
    Led();
    Led(int pin);
    void on();
    void off();
    void toggle();
};