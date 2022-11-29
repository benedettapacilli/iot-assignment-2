#pragma once
#include "../utils/Task.h"
#include "../utils/Situation.h"
#include <Arduino.h>

extern Situation situation;
extern ValveState valveState;
extern bool bridgeLightStatus;
extern int waterLevel;
extern bool guiManualEngaged;
extern int guiManualValveOpeningDegrees;

class ConnectorTask : public Task
{
public:
    ConnectorTask();
    void init(int period);
    void tick();
};