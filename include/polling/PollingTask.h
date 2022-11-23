#pragma once
#include "../utils/Task.h"
#include "Arduino.h"
#define PEnormal 2000
#define PEprealarm 1000
#define PEalarm 500

class PollingTask : public Task
{
private:
    int sonarTrigPin; // trig 9
    int sonarEchoPin; // echo 8
    int lastTimePolled;

public:
    PollingTask(int sonarPin1, int sonarPin2);
    int pollWaterLevel();
    void init(int period);
    void tick();
    int waterLevel;
};