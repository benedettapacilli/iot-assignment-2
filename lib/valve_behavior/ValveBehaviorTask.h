#pragma once
#include "../utils/Task.h"
#include "../utils/Potentiometer.h"
#include "../utils/Button.h"
#include "../utils/Situation.h"
#include "../utils/utilities.h"
#include "ServoTimer2.h"

extern Situation situation;
extern int waterLevel;
extern unsigned int valveOpening;

enum ValveState
{
    CLOSED,
    AUTO,
    MANUAL
};

class ValveBehaviorTask : public Task
{
private:
    Potentiometer pot;
    ServoTimer2 servo;
    Button button;
    ValveState valveState;
    bool buttonBeingPressed = false;
    unsigned long lastTimeMoved;

    void closeValve();
    void openValveAuto();
    void openValveManual();
    void openValveToAngle(int newAngle);

public:
    ValveBehaviorTask(int potPin, int servoPin, int buttonPin);
    void init(int period);
    void tick();
};
