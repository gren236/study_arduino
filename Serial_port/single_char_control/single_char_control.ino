const int LED = 9;
char data;

void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
}

void loop() {
    // if there is a symbol in buffer
    if (Serial.available() > 0) {
        data = Serial.read(); // then read a data byte

        // Turn on LED
        if (data == '1') {
            digitalWrite(LED, HIGH);
            Serial.println("LED ON");
        } else if (data == '0') {
            digitalWrite(LED, LOW);
            Serial.println("LED OFF");
        }
    }
}