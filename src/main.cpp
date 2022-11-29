/*
ASSIGNMENT 2 - 2022/2023
Salvatore Antonio Addimando 0000970539 - salvatore.addimando@studio.unibo.it
Benedetta Pacilli 0000975296 - benedetta.pacilli@studio.unibo.it
Valentina Pieri 0000974789 - valentina.pieri5@studio.unibo.it
*/

#include <Arduino.h>
#include "../lib/utils/Scheduler.h"
#include "../lib/utils/Scheduler.cpp"
#include "../lib/smart_lighting/SmartLightingTask.h"
#include "../lib/polling/PollingTask.h"
#include "../lib/valve_behavior/ValveBehaviorTask.h"
#include "../lib/connector/ConnectorTask.h"
#include "../lib/utils/utilities.h"

#define SMART_LIGHTING_TASK_PERIOD 100
#define POLLING_TASK_PERIOD gcd_ctz(LCD_REFRESH_INTERVAL, gcd_ctz(PEnormal, gcd_ctz(PEprealarm, gcd_ctz(PEalarm, BLINKING_INTERVAL))))
#define VALVE_BEHAVIOR_TASK_PERIOD POLLING_TASK_PERIOD
#define CONNECTOR_TASK_PERIOD 100

#define LA_PIN 2
#define PIR_PIN 3
#define LB_PIN 4
#define LC_PIN 5
#define SONAR_TRIG_PIN 9
#define SONAR_ECHO_PIN 8
#define LS_PIN A0
#define POT_PIN A1
#define SERVO_PIN 10
#define BUTTON_PIN 6

Scheduler scheduler;

void setup()
{
    Serial.begin(9600);
    Serial.setTimeout(0);
    scheduler.init(gcd_ctz(SMART_LIGHTING_TASK_PERIOD, POLLING_TASK_PERIOD));

    Task *smartLightingTask = new SmartLightingTask(PIR_PIN, LS_PIN, LA_PIN);
    Task *pollingTask = new PollingTask(SONAR_TRIG_PIN, SONAR_ECHO_PIN, LB_PIN, LC_PIN);
    Task *valveBehaviorTask = new ValveBehaviorTask(POT_PIN, SERVO_PIN, BUTTON_PIN);
    Task *connectorTask = new ConnectorTask();

    smartLightingTask->init(SMART_LIGHTING_TASK_PERIOD);
    pollingTask->init(POLLING_TASK_PERIOD);
    valveBehaviorTask->init(VALVE_BEHAVIOR_TASK_PERIOD);
    connectorTask->init(CONNECTOR_TASK_PERIOD);

    scheduler.addTask(smartLightingTask);
    scheduler.addTask(pollingTask);
    scheduler.addTask(valveBehaviorTask);
    scheduler.addTask(connectorTask);
}

void loop()
{
    scheduler.schedule();
}
