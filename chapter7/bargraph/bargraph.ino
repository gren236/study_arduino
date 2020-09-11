const int SER = 8; // DATA output pin
const int RCLK = 9; // LATCH output pin
const int SRCLK = 10; // CLOCK output pin

const int DIST = 0; // AO pin for IR sensor

int vals[9] = {0,1,3,7,15,31,63,127,255}; // Possible LED values
int maxVal = 500; // Max distance value
int minVal = 0; // Min distance value

void setup() {
    pinMode(SER, OUTPUT);
    pinMode(RCLK, OUTPUT);
    pinMode(SRCLK, OUTPUT);
}

void loop() {
    int distance = analogRead(DIST);
    distance = map(distance, minVal, maxVal, 0, 8);
    distance = constrain(distance, 0, 8);

    digitalWrite(RCLK, LOW); // LATCH is LOW
    shiftOut(SER, SRCLK, MSBFIRST, vals[distance]); // Higher bit is first
    digitalWrite(RCLK, HIGH); // LATCH is HIGH - flushing register to output

    delay(10);
}