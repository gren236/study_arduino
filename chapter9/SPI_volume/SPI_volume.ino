#include <SPI.h>

// Default pins for SPI lib are:
// 11 = MOSI, 12 = MISO, 13 = CLK
const int SS1 = 10;
const byte REG = B00010000; // Write 0 to registry command (choose POT 1)

// 120 (far) to 500 (close)
const int IR = 0; // Connecting IR sensor to analog pin A0

const int SPEAKER = 9; // Connected speaker pin
int freq = 800; // Speaker tone frequency

void setup() {
    pinMode(SS1, OUTPUT);
    pinMode(SPEAKER, OUTPUT);

    Serial.begin(9600); // Init serial port interface at speed 9600
    SPI.begin();
}

// Choose and send data to specific REG
// Chip 1 (SS 10) reg 1 - speaker
void setReg(int SS, int reg, int level) {
    digitalWrite(SS, LOW); // Choose chip by setting SS to 0
    SPI.transfer(reg);
    SPI.transfer(level);
    digitalWrite(SS, HIGH); // Set SS to 1 (stop transfering data)
}

void loop() {
    tone(SPEAKER, freq);

    int val = analogRead(IR); // Reading from A0
    Serial.println(val);

    int volume = map(val, 120, 500, 0, 128);
    volume = constrain(volume, 0, 128);

    setReg(SS1, REG, volume);
}