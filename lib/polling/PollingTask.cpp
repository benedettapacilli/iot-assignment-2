#include "../../include/polling/PollingTask.h"
#include "../../include/utils/Situation.h"

PollingTask::PollingTask(int trigPin, int echoPin)
{
    this->sonar = Sonar(trigPin, echoPin);
}

void PollingTask::init(int period)
{
    Task::init(period);
    this->pollWaterLevel();
}

void PollingTask::tick()
{
    switch (situation)
    {
    case NORMAL:
        this->currentPE = PEnormal;
        break;

    case PREALARM:
        this->currentPE = PEprealarm;
        break;

    case ALARM:
        this->currentPE = PEalarm;
        break;
    }

    if (millis() - lastTimePolled >= currentPE)
    {
        this->pollWaterLevel();
    }
}

void PollingTask::pollWaterLevel()
{
    this->lastTimePolled = millis();
    this->waterLevel = this->sonar.getDistance();
}