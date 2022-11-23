#include "../../include/polling/PollingTask.h"
#include "../../include/utils/Situation.h"

PollingTask::PollingTask(int sonarPin1, int sonarPin2)
{
    this->sonarTrigPin = sonarTrigPin;
    this->sonarEchoPin = sonarEchoPin;
}

void PollingTask::init(int period)
{
    Task::init(period);
    pinMode(this->sonarTrigPin, OUTPUT);
    pinMode(this->sonarEchoPin, INPUT);
    this->waterLevel = pulseIn(this->sonarEchoPin, HIGH) / 58.2;
    this->lastTimePolled = millis();
}

void PollingTask::tick()
{
    switch (situation)
    {
    case NORMAL:
        if (millis() - lastTimePolled >= PEnormal)
        {
            this->waterLevel = this->pollWaterLevel();
            lastTimePolled = millis();
        }
        break;

    case PREALARM:
        if (millis() - lastTimePolled >= PEprealarm)
        {
            this->waterLevel = this->pollWaterLevel();
            lastTimePolled = millis();
        }
        break;

    case ALARM:
        if (millis() - lastTimePolled >= PEalarm)
        {
            this->waterLevel = this->pollWaterLevel();
            lastTimePolled = millis();
        }
        break;
    }
}

int PollingTask::pollWaterLevel()
{
    digitalWrite(this->sonarTrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(this->sonarTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->sonarTrigPin, LOW);
    return pulseIn(this->sonarEchoPin, HIGH) / 58.2;
}