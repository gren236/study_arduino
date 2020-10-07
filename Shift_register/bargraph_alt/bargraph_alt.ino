/**
 * This is the same program as bargraph, but made without vals preset. It uses bit shifts and logical OR.
**/
const int SER = 8; // DATA output pin
const int RCLK = 9; // LATCH output pin
const int SRCLK = 10; // CLOCK output pin

const int DIST = 0; // AO pin for IR sensor

int maxVal = 500; // Max distance value
int minVal = 0; // Min distance value

void setup() {
    pinMode(SER, OUTPUT);
    pinMode(RCLK, OUTPUT);
    pinMode(SRCLK, OUTPUT);
}////////////////////////////////////////

void loop() {
    int distance = analogRead(DIST);
    distance = map(distance, minVal, maxVal, 0, 8);
    distance = constrain(distance, 0, 8);
    
    int val = B00000001;
    for (int i = 0; i < distance; i++) {
        val <<= 1;
        val |= 1;
    }

    digitalWrite(RCLK, LOW); // LATCH is LOW
    shiftOut(SER, SRCLK, MSBFIRST, val); // Higher bit is first
    digitalWrite(RCLK, HIGH); // LATCH is HIGH - flushing register to output

    delay(10);
}