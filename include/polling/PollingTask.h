#pragma once
#include "Arduino.h"
#include "../utils/Task.h"
#include "../utils/Sonar.h"
#include "../utils/Led.h"
#include "../utils/Potentiometer.h"
#include "LiquidCrystal_I2C.h"

#define PEnormal 2000
#define PEprealarm 1000
#define PEalarm 500
#define WL1 50
#define WL2 100
#define WLMAX 150
#define BLINKING_INTERVAL 2000

LiquidCrystal_I2C lcd;

class PollingTask : public Task
{
private:
    Sonar sonar;
    int lastTimePolled;
    int lastTimeBlinked;
    int currentPE;
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