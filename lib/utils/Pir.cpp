#include "../../include/utils/Pir.h"

Pir::Pir()
{
}

Pir::Pir(int pin)
{
    this->pin = pin;
}

bool Pir::detect()
{
    return digitalRead(pin);
}

