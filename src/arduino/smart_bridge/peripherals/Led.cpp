#include "Led.h"

Led::Led()
{
}

Led::Led(int pin)
{
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
}

void Led::on()
{
  digitalWrite(this->pin, HIGH);
}

void Led::off()
{
  digitalWrite(this->pin, LOW);
}

void Led::toggle()
{
  digitalWrite(this->pin, !digitalRead(this->pin));
}
