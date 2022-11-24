#include "SmartLightingTask.h"

SmartLightingTask::SmartLightingTask(int pirPin, int lsPin, int laPin)
{
    this->ls = LightSensor(lsPin);
    this->led = Led(laPin);
    this->pir = Pir(pirPin);
}

void SmartLightingTask::init(int period)
{
    Task::init(period);
    this->state = IDLE;
    Serial.println("IDLE");
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
            Serial.println("DETECTED");
        }
        else if (situation == ALARM)
        {
            this->state = OFF;
            Serial.println("OFF");
        }
        break;
    }

    case DETECTED:
    {
        if (this->ls.getLightLevel() < THl)
        {
            this->led.on();
        }
        else
        {
            this->led.off();
        }

        if (this->pir.detect())
        {
            this->T1offset = millis();
        }
        else if (millis() - this->T1offset > T1)
        {
            this->led.off();
            this->state = IDLE;
            Serial.println("IDLE");
        }

        if (situation == ALARM)
        {
            this->state = OFF;
            Serial.println("OFF");
        }
        break;
    }

    case OFF:
        this->led.off();

        if (situation == NORMAL || situation == PREALARM)
        {
            this->state = IDLE;
            Serial.println("IDLE");
        }
        break;
    }
}