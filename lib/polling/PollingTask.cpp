#include "../../include/polling/PollingTask.h"
#include "../../include/utils/Situation.h"

PollingTask::PollingTask(int trigPin, int echoPin)
{
    this->sonar = Sonar(trigPin, echoPin);
}

void PollingTask::init(int period)
{
    Task::init(period);
    this->waterLevel = pollWaterLevel();
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
    return this->sonar.getDistance();
}