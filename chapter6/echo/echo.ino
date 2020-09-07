char data; // Current symbol

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) { // Check if data in buffer is available
        data = Serial.read(); // Reading byte from buffer
        Serial.print(data);
    }
}
