#include <Arduino.h>
#include "../include/utils/Scheduler.h"
#include "../lib/utils/Scheduler.cpp"
#include "../include/smart_lighting/SmartLightingTask.h"

#define PIR_PIN 3
#define LS_PIN A0
#define LA_PIN 2

Scheduler scheduler;

void setup()
{
    Serial.begin(9600);
    scheduler.init(100);

    Task *smartLightingTask = new SmartLightingTask(PIR_PIN, LS_PIN, LA_PIN);
    smartLightingTask->init(100);

    scheduler.addTask(smartLightingTask);
}

void loop()
{
    scheduler.schedule();
}