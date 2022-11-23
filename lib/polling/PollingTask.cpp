#include "../../include/polling/PollingTask.h"
#include "../../include/utils/Situation.h"

PollingTask::PollingTask(int trigPin, int echoPin, int lbPin, int lcPin, int potPin)
{
    this->sonar = Sonar(trigPin, echoPin);
    this->lb = Led(lbPin);
    this->lc = Led(lcPin);
    this->pot = Potentiometer(potPin);
    lcd = LiquidCrystal_I2C(0x27, 20, 4);
}

void PollingTask::init(int period)
{
    Task::init(period);
    this->pollWaterLevel();
    this->lastTimeBlinked = millis();
    lcd.init();
    lcd.backlight();
}

void PollingTask::tick()
{
    if (this->waterLevel >= 0 && this->waterLevel <= WL1)
    {
        situation = NORMAL;
    }
    else if (this->waterLevel > WL1 && this->waterLevel <= WL2)
    {
        situation = PREALARM;
    }
    else if (this->waterLevel > WL2 && this->waterLevel <= WLMAX)
    {
        situation = ALARM;
    }

    switch (situation)
    {
    case NORMAL:
        this->currentPE = PEnormal;
        this->lb.on();
        this->lc.off();
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
    this->waterLevel = (distance > WLMAX) ? WLMAX : distance;
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
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pre-alarm");
    lcd.setCursor(0, 1);
    lcd.print("Water level: ");
    lcd.print(this->waterLevel);
}

void PollingTask::showAlarmInfo()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Alarm");
    lcd.setCursor(0, 1);
    lcd.print("Water level: ");
    lcd.print(this->waterLevel);
    lcd.setCursor(0, 2);
    lcd.print("Valve opening: ");
    lcd.print(getValveOpeningDegree());
}

int PollingTask::getValveOpeningDegree()
{
    return map(this->pot.read(), 0, 1023, 0, 180);
}