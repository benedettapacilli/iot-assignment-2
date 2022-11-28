#pragma once
#include "../utils/Task.h"
#include "../utils/Situation.h"
#include <Arduino.h>

extern Situation situation;
extern bool bridgeLightStatus;
extern int waterLevel;

class ConnectorTask : public Task
{
public:
    ConnectorTask();
    void init(int period);
    void tick();
};