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

    String line = Serial.readString();
    if (line.length() > 0 && line[0] == 's')
    {
        if (valveState == AUTO)
        {
            valveState = MANUAL;
            guiManualEngaged = true;
        }
        else if (valveState == MANUAL)
        {
            valveState = AUTO;
            guiManualEngaged = false;
        }
    }

    if (guiManualEngaged)
    {
        if (line.length() > 0 && line[0] == 'v')
        {
            guiManualValveOpeningDegrees = line.substring(2).toInt();
        }
    }
}
