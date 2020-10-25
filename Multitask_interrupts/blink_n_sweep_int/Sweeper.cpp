#include "Sweeper.h"
#include <Arduino.h>

Sweeper::Sweeper(int interval)
{
    updateInterval = interval;
    increment = 1;
}

void Sweeper::Attach(int pin)
{
    servo.attach(pin);
}

void Sweeper::Detach()
{
    servo.detach();
}

void Sweeper::Update(unsigned long currentMillis)
{
    if ((currentMillis - lastUpdate) > updateInterval)
    {
        lastUpdate = currentMillis;
        pos += increment;
        servo.write(pos);
        Serial.println(pos);

        if ((pos >= 180) || (pos <= 0))
        {
            // Reverse direction
            increment = -increment;
        }
    }
}

void Sweeper::Reset()
{
    pos = 0;
    servo.write(pos);
    increment = abs(increment);
}