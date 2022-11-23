#pragma once
#include "../utils/Task.h"
#include "../utils/Sonar.h"
#include "Arduino.h"
#define PEnormal 2000
#define PEprealarm 1000
#define PEalarm 500

class PollingTask : public Task
{
private:
    Sonar sonar;
    int lastTimePolled;

public:
    PollingTask(int trigPin, int echoPin);
    int pollWaterLevel();
    void init(int period);
    void tick();
    int waterLevel;
};