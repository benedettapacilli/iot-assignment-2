#pragma once
#include "../task_architecture/Task.h"
#include "../peripherals/Potentiometer.h"
#include "../peripherals/Button.h"
#include "../utils/Situation.h"
#include "../utils/utilities.h"
#include "../utils/ServoTimer2.h"

extern Situation situation;
extern ValveState valveState;
extern int waterLevel;
extern unsigned int valveOpening;
extern bool guiManualEngaged;
extern int guiManualValveOpeningDegrees;

class ValveBehaviorTask : public Task
{
private:
    Potentiometer pot;
    ServoTimer2 servo;
    Button button;
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
