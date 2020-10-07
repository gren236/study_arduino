#include <Servo.h>
const int SERVO = 9; // Pin 9 to connect servo

const int POT = 0; // Analog pin to connect potentiometer

Servo myServo;

int val = 0; // Var to read potentiometer values

void setup() {
    myServo.attach(SERVO);
}

void loop() {
    val = analogRead(POT);
    val = map(val, 0, 1023, 0, 179);
    myServo.write(val);
    delay(15);
}