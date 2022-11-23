#include "../../include/smart_lighting/SmartLightingTask.h"
#include "../../include/utils/Situation.h"

SmartLightingTask::SmartLightingTask(int sensorPin, int lsPin, int laPin)
{
    this->pirPin = sensorPin;
    this->lsPin = lsPin;
    this->led = Led(laPin);
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
        int detected = digitalRead(this->pirPin);

        if (detected)
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

        int detected = digitalRead(this->pirPin);

        if (detected)
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