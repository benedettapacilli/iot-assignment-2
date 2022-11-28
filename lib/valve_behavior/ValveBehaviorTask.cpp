#include "ValveBehaviorTask.h"

ValveBehaviorTask::ValveBehaviorTask(int potPin, int servoPin, int buttonPin)
{
    this->pot = Potentiometer(potPin);
    this->button = Button(buttonPin);
    this->servo.attach(servoPin);
    this->valveState = CLOSED;
}

void ValveBehaviorTask::init(int period)
{
    Task::init(period);
    this->lastTimeMoved = millis();
}

void ValveBehaviorTask::tick()
{
    switch (this->valveState)
    {
    case CLOSED:
        closeValve();
        if (situation != NORMAL && situation != PREALARM)
        {
            this->valveState = AUTO;
        }
        break;
    case AUTO:
        openValveAuto();
        if (situation == NORMAL || situation == PREALARM)
        {
            this->valveState = CLOSED;
        }
        else if (this->button.isPressed() && !this->buttonBeingPressed)
        {
            this->buttonBeingPressed = true;
            this->valveState = MANUAL;
        }
        else if (!this->button.isPressed())
        {
            this->buttonBeingPressed = false;
        }
        break;
    case MANUAL:
        openValveManual();
        if (situation == NORMAL || situation == PREALARM)
        {
            this->valveState = CLOSED;
        }
        else if (this->button.isPressed() && !this->buttonBeingPressed)
        {
            this->buttonBeingPressed = true;
            this->valveState = AUTO;
        }
        else if (!this->button.isPressed())
        {
            this->buttonBeingPressed = false;
        }
        break;
    }
}

void ValveBehaviorTask::closeValve()
{
    this->openValveToAngle(0);
}

void ValveBehaviorTask::openValveAuto()
{
    this->openValveToAngle(map(waterLevel, 66, 100, 0, 180));
}

void ValveBehaviorTask::openValveManual()
{
    this->openValveToAngle(map(this->pot.read(), 0, 1023, 0, 180));
}

void ValveBehaviorTask::openValveToAngle(int newAngle)
{
    unsigned int micros = degree2ms(newAngle);
    if (millis() - lastTimeMoved > 15)
    {
        this->servo.write(micros);
        lastTimeMoved = millis();
        valveOpening = newAngle;
    }
}