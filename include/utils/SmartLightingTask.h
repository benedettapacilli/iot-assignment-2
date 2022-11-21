#pragma once
#include "Task.h"
#include "Led.h"
#define THl 500
#define T1 1000

class SmartLightingTask : public Task
{
private:
    int pirPin;
    int lsPin;
    Led led;
    int T1offset;

public:
    State state;
    SmartLightingTask(int pirPin, int lsPin, int laPin);
    void init(int period);
    void tick();
};

enum State
{
    IDLE,
    DETECTED,
    OFF
};