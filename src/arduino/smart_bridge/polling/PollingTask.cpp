#include "PollingTask.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

PollingTask::PollingTask(int trigPin, int echoPin, int lbPin, int lcPin)
{
    this->sonar = Sonar(trigPin, echoPin);
    this->lb = Led(lbPin);
    this->lc = Led(lcPin);
}

void PollingTask::init(int period)
{
    Task::init(period);
    this->pollWaterLevel();
    this->lastTimeBlinked = millis();
    lcd.init();
}

void PollingTask::tick()
{
    if (waterLevel >= 0 && waterLevel <= WL1)
    {
        situation = NORMAL;
    }
    else if (waterLevel > WL1 && waterLevel <= WL2)
    {
        situation = PREALARM;
    }
    else if (waterLevel > WL2 && waterLevel <= WLMAX)
    {
        situation = ALARM;
    }

    switch (situation)
    {
    case NORMAL:
        this->currentPE = PEnormal;
        this->lb.on();
        this->lc.off();
        lcd.clear();
        lcd.noBacklight();
        break;

    case PREALARM:
        this->currentPE = PEprealarm;
        this->blinkLc();
        showPreAlarmInfo();
        break;

    case ALARM:
        this->currentPE = PEalarm;
        this->lb.off();
        this->lc.on();

        showAlarmInfo();
        break;
    }

    if (millis() - lastTimePolled >= currentPE)
    {
        this->pollWaterLevel();
    }
}

void PollingTask::pollWaterLevel()
{
    this->lastTimePolled = millis();
    int distance = this->sonar.getDistance();
    waterLevel = WLMAX - ((distance == 0 || distance > WLMAX) ? WLMAX : distance);
}

void PollingTask::blinkLc()
{
    if (millis() - lastTimeBlinked >= BLINKING_INTERVAL)
    {
        this->lastTimeBlinked = millis();
        this->lc.toggle();
    }
}

void PollingTask::showPreAlarmInfo()
{
    if (millis() - lastTimeLCDRefreshed >= LCD_REFRESH_INTERVAL)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pre-alarm");
        lcd.setCursor(0, 1);
        lcd.print("Water level: ");
        lcd.print(waterLevel);
        lcd.backlight();
        this->lastTimeLCDRefreshed = millis();
    }
}

void PollingTask::showAlarmInfo()
{
    if (millis() - lastTimeLCDRefreshed >= LCD_REFRESH_INTERVAL)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Alarm");
        lcd.setCursor(0, 1);
        lcd.print("Water level: ");
        lcd.print(waterLevel);
        lcd.setCursor(0, 2);
        lcd.print("Valve opening: ");
        lcd.print(valveOpening);
        lcd.backlight();
        this->lastTimeLCDRefreshed = millis();
    }
}