const int LED = 9;

void setup() {
  pinMode(LED, OUTPUT); // Configure pin as output
}

void loop() {
  for (int i = 0; i < 256; i++) {
    analogWrite(LED, i); // Write as analog signal using PWM
    delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    analogWrite(LED, i);
    delay(10);
  }
}
