#include <Arduino.h>
#include "../lib/utils/Scheduler.h"
#include "../lib/utils/Scheduler.cpp"
#include "../lib/smart_lighting/SmartLightingTask.h"
#include "../lib/polling/PollingTask.h"
#include "../lib/utils/utilities.h"

#define SMART_LIGHTING_TASK_PERIOD 100
#define POLLING_TASK_PERIOD gcd_ctz(500, gcd_ctz(PEnormal, gcd_ctz(PEprealarm, gcd_ctz(PEalarm, BLINKING_INTERVAL))))

#define LA_PIN 2
#define PIR_PIN 3
#define LB_PIN 4
#define LC_PIN 5
#define SONAR_TRIG_PIN 9
#define SONAR_ECHO_PIN 8
#define LS_PIN A0
#define POT_PIN A1

Scheduler scheduler;

void setup()
{
    Serial.begin(9600);
    scheduler.init(gcd_ctz(SMART_LIGHTING_TASK_PERIOD, POLLING_TASK_PERIOD));

    Task *smartLightingTask = new SmartLightingTask(PIR_PIN, LS_PIN, LA_PIN);
    Task *pollingTask = new PollingTask(SONAR_TRIG_PIN, SONAR_ECHO_PIN, LB_PIN, LC_PIN, POT_PIN);

    smartLightingTask->init(SMART_LIGHTING_TASK_PERIOD);
    pollingTask->init(POLLING_TASK_PERIOD);

    scheduler.addTask(smartLightingTask);
    scheduler.addTask(pollingTask);
}

void loop()
{
    scheduler.schedule();
}
