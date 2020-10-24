#include "Flasher.h"

Flasher led1(12, 500);
Flasher led2(13, 1000);

void setup()
{
    // N/A
}

void loop()
{
    led1.Update();
    led2.Update();
}