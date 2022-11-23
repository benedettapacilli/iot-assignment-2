#include "../../include/smart_lighting/SmartLightingTask.h"
#include "../../include/utils/Situation.h"

SmartLightingTask::SmartLightingTask(int pirPin, int lsPin, int laPin)
{
    this->lsPin = lsPin;
    this->led = Led(laPin);
    this->pir = Pir(pirPin);
}

void SmartLightingTask::init(int period)
{
    Task::init(period);
    this->state = IDLE;
}

void SmartLightingTask::tick()
{
    if (situation == ALARM)
    {
        this->state = OFF;
    }

    switch (this->state)
    {
    case IDLE:
    {
        Serial.println("IDLE");

        if (this->pir.detect())
        {
            state = DETECTED;
            this->T1offset = millis();
        }
        break;
    }

    case DETECTED:
    {
        Serial.println("DETECTED");
        int lsValue = analogRead(this->lsPin);
        if (lsValue < THl)
        {
            this->led.on();
        }
        else
        {
            this->state = IDLE;
            this->led.off();
        }

        if (this->pir.detect())
        {
            this->T1offset = millis();
        }

        if (millis() - this->T1offset > T1)
        {
            this->led.off();
            this->state = IDLE;
        }
        break;
    }

    case OFF:
        Serial.println("OFF");
        this->led.off();

        if (situation == NORMAL || situation == PREALARM)
        {
            this->state = IDLE;
        }
        break;
    }
}