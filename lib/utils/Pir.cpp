#include "../../include/utils/Pir.h"

Pir::Pir()
{
}

Pir::Pir(int pin)
{
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

bool Pir::detect()
{
    return digitalRead(this->pin);
}
