#pragma once
#include "../utils/Task.h"
#include "../utils/Led.h"
#include "../utils/Pir.h"
#include "../utils/LightSensor.h"
#include "SmartLightingState.h"
#define THl 500
#define T1 5000

class SmartLightingTask : public Task
{
private:
    LightSensor ls;
    Led led;
    Pir pir;
    unsigned long T1offset;

public:
    SmartLightingState state;
    SmartLightingTask(int pirPin, int lsPin, int laPin);
    void init(int period);
    void tick();
};