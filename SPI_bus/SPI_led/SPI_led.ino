#include <SPI.h>

// Default pins for SPI lib are:
// 11 = MOSI, 12 = MISO, 13 = CLK

const int SS1 = 10;
const int SS2 = 9;
const byte REG0 = B00000000; // Write 0 to registry command (choose POT 1)
const byte REG1 = B00010000; // Write 1 to registry command (choose POT 2)

void setup()
{
    // Set SS pins to OUTPUT
    pinMode(SS1, OUTPUT);
    pinMode(SS2, OUTPUT);
    // Init hardware SPI
    SPI.begin();
}

// Choose and send data to specific LED
// Chip 1 (SS 10) reg 0 - red
// Chip 1 (SS 10) reg 1 - yellow
// Chip 2 (SS 9)  reg 0 - green
// Chip 2 (SS 9)  reg 1 - blue
void setLed(int SS, int reg, int level) {
    digitalWrite(SS, LOW); // Choose chip by setting SS to 0
    SPI.transfer(reg);
    SPI.transfer(level);
    digitalWrite(SS, HIGH); // Set SS to 1 (stop transfering data)
}

void loop()
{
    for(int i = 0; i < 128; i++){
        setLed(SS1, REG0, i); // red
        setLed(SS1, REG1, i); // yellow
        setLed(SS2, REG0, i); // green
        setLed(SS2, REG1, i); // blue
        delay(10);
    }
    delay(300);

    for (int i = 128; i >= 0; i--)
    {
        setLed(SS1, REG0, i); // red
        setLed(SS1, REG1, i); // yellow
        setLed(SS2, REG0, i); // green
        setLed(SS2, REG1, i); // blue
        delay(10);
    }
    delay(300);    
}