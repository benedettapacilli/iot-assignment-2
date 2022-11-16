#pragma once
 
class Led
{
    private:
        int pin;
        int state;

    public:
        Led(int pin);
        void on();
        void off();
        void toggle();
    
};