const int SER = 8; // DATA output pin

const int RCLK = 9; // LATCH output pin
const int SRCLK = 10; // CLOCK output pin

int seq[14] = {1,2,4,8,16,32,64,128,64,32,16,8,4,2}; // Animation sequence

void setup() {
    pinMode(SER, OUTPUT);
    pinMode(RCLK, OUTPUT);
    pinMode(SRCLK, OUTPUT);
}

void loop() {
    // for (int i = 0; i < 14; i++) {
    //     digitalWrite(RCLK, LOW); // LATCH is LOW
    //     shiftOut(SER, SRCLK, MSBFIRST, seq[i]); // Higher bit is first
    //     digitalWrite(RCLK, HIGH); // LATCH is HIGH - flushing register to output
    //     delay(100);
    // }
    alternative();
}

// Another way of doing lightrider without preset sequence
void alternative() {
    int val = B00000001;
    bool direction = true;
    for (int i = 0; i < 14; i++) {
        digitalWrite(RCLK, LOW); // LATCH is LOW
        shiftOut(SER, SRCLK, MSBFIRST, val); // Higher bit is first
        digitalWrite(RCLK, HIGH); // LATCH is HIGH - flushing register to output

        if (direction == true)
            val <<= 1;
        else
            val >>= 1;
        
        if (val == 128) direction = !direction; // Change direction if value is 10000000

        delay(100);
    }
}