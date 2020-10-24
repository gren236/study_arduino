#ifndef Sweeper_h
#define Sweeper_h

#include <Servo.h>

class Sweeper
{
    Servo servo;
    int pos;
    int increment; // increment interval
    int updateInterval; // interval between updates (ms)
    unsigned long lastUpdate; // last position update

public:
    Sweeper(int interval);

    void Attach(int pin);
    void Detach();
    void Update();
};

#endif