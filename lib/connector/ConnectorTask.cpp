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
    Serial.print("s ");
    Serial.println(situation);
    Serial.print("b ");
    Serial.println(bridgeLightStatus);
    Serial.print("w ");
    Serial.println(waterLevel);
    Serial.print("v ");
    Serial.println(valveState);
}
