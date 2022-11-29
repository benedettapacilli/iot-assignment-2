#include "Sonar.h"

Sonar::Sonar()
{
}

Sonar::Sonar(int trigPin, int echoPin)
{
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(this->trigPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
}

unsigned long Sonar::getDistance()
{
    digitalWrite(this->trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(this->trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trigPin, LOW);
    return pulseIn(this->echoPin, HIGH, 12000) * 0.0343 / 2;
}