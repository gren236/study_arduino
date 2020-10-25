#include "Arduino.h"
#include "Flasher.h"

Flasher::Flasher(int pin, long blink)
{
    ledPin = pin;
    blinkTime = blink;

    pinMode(ledPin, OUTPUT);

    ledState = LOW;
    previousMillis = 0;
}

void Flasher::Update(unsigned long currentMillis)
{
    if ((currentMillis - previousMillis) >= blinkTime)
    {
        if (ledState == HIGH)
        {
            digitalWrite(ledPin, LOW);
            ledState = LOW;
        }
        else
        {
            digitalWrite(ledPin, HIGH);
            ledState = HIGH;
        }
        previousMillis = currentMillis;
    }
}