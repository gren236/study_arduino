#include "Flasher.h"
#include "Sweeper.h"

Flasher led1(12, 500);
Flasher led2(13, 1000);
Sweeper sweeper1(15);

void setup()
{
    Serial.begin(9600);
    sweeper1.Attach(9);
}

void loop()
{
    sweeper1.Update();

    led1.Update();
    led2.Update();
}