#pragma once
#include "../task_architecture/Task.h"
#include "../peripherals/Led.h"
#include "../peripherals/Pir.h"
#include "../peripherals/LightSensor.h"
#include "../utils/Situation.h"
#include "SmartLightingState.h"

extern Situation situation;
extern bool bridgeLightStatus;

#define THl 500
#define T1 5000

class SmartLightingTask : public Task
{
private:
    LightSensor ls;
    Led la;
    Pir pir;
    unsigned long T1offset;

public:
    SmartLightingState state;
    SmartLightingTask(int pirPin, int lsPin, int laPin);
    void init(int period);
    void tick();
};