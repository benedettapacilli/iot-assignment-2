#include <Arduino.h>
#include "../lib/utils/Scheduler.h"
#include "../lib/utils/Scheduler.cpp"
#include "../lib/smart_lighting/SmartLightingTask.h"
#include "../lib/polling/PollingTask.h"

#define PIR_PIN 3
#define LS_PIN A0
#define LA_PIN 2
#define LB_PIN 4
#define LC_PIN 5
#define SONAR_TRIG_PIN 9
#define SONAR_ECHO_PIN 8
#define POT_PIN A1

Scheduler scheduler;

void setup()
{
    Serial.begin(9600);
    scheduler.init(100);

    Task *smartLightingTask = new SmartLightingTask(PIR_PIN, LS_PIN, LA_PIN);
    Task *pollingTask = new PollingTask(SONAR_TRIG_PIN, SONAR_ECHO_PIN, LB_PIN, LC_PIN, POT_PIN);

    smartLightingTask->init(100);
    pollingTask->init(100);

    scheduler.addTask(smartLightingTask);
    scheduler.addTask(pollingTask);
}

void loop()
{
    scheduler.schedule();
}
