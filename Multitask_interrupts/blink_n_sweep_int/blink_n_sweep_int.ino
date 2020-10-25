#include <Arduino.h>
#include "Flasher.h"
#include "Sweeper.h"

Flasher led1(12, 500);
Flasher led2(13, 1000);
Sweeper sweeper1(15);

void Reset()
{
    sweeper1.Reset();
}

void setup()
{
    Serial.begin(9600);
    sweeper1.Attach(9);

    // Set an interruption
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);

    attachInterrupt(0, Reset, FALLING);
}

SIGNAL(TIMER0_COMPA_vect)
{
    unsigned long currentMillis = millis();

    // Turn off led and sweeper if button is pressed
    // if (digitalRead(2) == HIGH)
    {
        sweeper1.Update(currentMillis);
        led1.Update(currentMillis);
    }

    led2.Update(currentMillis);
}

void loop()
{
}