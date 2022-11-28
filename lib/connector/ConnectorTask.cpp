#include "ConnectorTask.h"

ConnectorTask::ConnectorTask()
{
}

void ConnectorTask::init(int period)
{
    Task::init(period);
}

void ConnectorTask::tick()
{
    Serial.println(situation);
    Serial.println(bridgeLightStatus);
    Serial.println(waterLevel);
}