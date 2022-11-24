#pragma once
#include <Arduino.h>

class Sonar
{
private:
    int trigPin;
    int echoPin;

public:
    Sonar();
    Sonar(int trigPin, int echoPin);
    unsigned long getDistance();
};