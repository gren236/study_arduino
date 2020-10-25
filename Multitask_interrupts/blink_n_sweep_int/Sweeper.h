#ifndef Sweeper_h
#define Sweeper_h

#include <Servo.h>

class Sweeper
{
    Servo servo;
    volatile int pos;
    volatile int increment; // increment interval
    int updateInterval; // interval between updates (ms)
    volatile unsigned long lastUpdate; // last position update

public:
    Sweeper(int interval);

    void Attach(int pin);
    void Detach();
    void Update(unsigned long currentMillis);
    void Reset();
};

#endif