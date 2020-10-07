const int MOTOR = 9;

void setup() {
  pinMode(MOTOR, OUTPUT);
}

void loop() {
  for (int i = 0; i < 256; i++) {
    analogWrite(MOTOR, i);
    delay(10);
  }
  
  delay(2000);
  
  for (int i = 255; i >= 0; i--) {
    analogWrite(MOTOR, i);
    delay(10);
  }
  
  delay(2000);
}
