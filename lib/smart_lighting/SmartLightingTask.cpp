#include "SmartLightingTask.h"

SmartLightingTask::SmartLightingTask(int pirPin, int lsPin, int laPin)
{
    this->ls = LightSensor(lsPin);
    this->la = Led(laPin);
    this->pir = Pir(pirPin);
}

void SmartLightingTask::init(int period)
{
    Task::init(period);
    this->state = IDLE;
}

void SmartLightingTask::tick()
{
    switch (this->state)
    {
    case IDLE:
    {
        if (this->pir.detect())
        {
            this->T1offset = millis();
            state = DETECTED;
        }
        else if (situation == ALARM)
        {
            this->state = OFF;
        }
        break;
    }

    case DETECTED:
    {
        if (this->ls.getLightLevel() < THl)
        {
            this->la.on();
        }
        else
        {
            this->la.off();
        }

        if (this->pir.detect())
        {
            this->T1offset = millis();
        }
        else if (millis() - this->T1offset > T1)
        {
            this->la.off();
            this->state = IDLE;
        }

        if (situation == ALARM)
        {
            this->state = OFF;
        }
        break;
    }

    case OFF:
        this->la.off();

        if (situation == NORMAL || situation == PREALARM)
        {
            this->state = IDLE;
        }
        break;
    }
}