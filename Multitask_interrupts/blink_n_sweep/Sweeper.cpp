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

void Sweeper::Update()
{
    if ((millis() - lastUpdate) > updateInterval)
    {
        lastUpdate = millis();
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