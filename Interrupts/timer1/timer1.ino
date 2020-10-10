#include <TimerOne.h>

const int LED = 13;

void setup()
{
    pinMode(LED, OUTPUT);
    Timer1.initialize(1000000);
    Timer1.attachInterrupt(blinky);
}

void loop()
{
    // No code this time
}

void blinky() {
    digitalWrite(LED, !digitalRead(LED));
}