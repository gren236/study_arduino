const int SER = 8; // DATA output pin

const int RCLK = 9; // LATCH output pin
const int SRCLK = 10; // CLOCK output pin

void setup() {
    pinMode(SER, OUTPUT);
    pinMode(RCLK, OUTPUT);
    pinMode(SRCLK, OUTPUT);

    digitalWrite(RCLK, LOW); // LATCH is LOW
    shiftOut(SER, SRCLK, MSBFIRST, 170); // Higher bit is first
    digitalWrite(RCLK, HIGH); // LATCH is HIGH - flushing register to output
}

void loop() {
    ;
}