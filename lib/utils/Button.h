#pragma once
#include <Arduino.h>

class Button
{
private:
    int pin;

public:
    Button();
    Button(int pin);
    bool isPressed();
};
