#pragma once
#include "../utils/Task.h"
#include "../utils/Sonar.h"
#include "../utils/Led.h"
#include "../utils/Potentiometer.h"
#include "../utils/Situation.h"
#include "LiquidCrystal_I2C.h"

#define PEnormal 2000
#define PEprealarm 1000
#define PEalarm 500
#define WL1 33
#define WL2 66
#define WLMAX 100
#define BLINKING_INTERVAL 2000

class PollingTask : public Task
{
private:
    Sonar sonar;
    unsigned long lastTimePolled;
    unsigned long lastTimeBlinked;
    unsigned long currentPE;
    Led lb;
    Led lc;
    Potentiometer pot;

    void pollWaterLevel();
    void blinkLc();
    void showPreAlarmInfo();
    void showAlarmInfo();
    int getValveOpeningDegree();

public:
    PollingTask(int trigPin, int echoPin, int lbPin, int lcPin, int potPin);
    void init(int period);
    void tick();
    int waterLevel;
};