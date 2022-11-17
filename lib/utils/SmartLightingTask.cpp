#include "../../include/utils/SmartLightingTask.h"

SmartLightingTask::SmartLightingTask(int sensorPin, int lsPin, int pinLa)
{
    this->pirPin = sensorPin;
    this->lsPin = lsPin;
    this->led = Led(pinLa);
}

void SmartLightingTask::init(int period)
{
    Task::init(period);
    this->state = IDLE;
}

void SmartLightingTask::tick()
{
    // TODO: check if situation is ALARM and if so, set state to OFF

    switch (this->state)
    {
    case IDLE:
        int detected = analogRead(this->pirPin);

        if (detected)
        {
            state = DETECTED;
            this->T1offset = millis();
        }
        break;

    case DETECTED:
        int lsValue = analogRead(this->lsPin);
        if (lsValue < THl)
        {
            this->led.on();
        }
        else
        {
            this->state = IDLE;
        }

        if (millis() - this->T1offset > T1)
        {
            this->state = IDLE;
        }
        break;

    case OFF:
        this->led.off();
        // TODO: check if situation is NORMAL or PREALARM and if so, set state to IDLE
        break;
    }
}