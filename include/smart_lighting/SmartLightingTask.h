#pragma once
#include "../utils/Task.h"
#include "../utils/Led.h"
#include "SmartLightingState.h"
#define THl 500
#define T1 5000

class SmartLightingTask : public Task
{
private:
    int pirPin;
    int lsPin;
    Led led;
    int T1offset;

public:
    SmartLightingState state;
    SmartLightingTask(int pirPin, int lsPin, int laPin);
    void init(int period);
    void tick();
};