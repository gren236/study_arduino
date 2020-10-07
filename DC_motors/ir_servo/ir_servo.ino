#include <Servo.h>
const int SERVO = 9; // Pin 9 connecting servo signal

const int IR = 0; // Analog pin connecting ir sensor

// LED outputs
const int LED1 = 3;
const int LED2 = 5;
const int LED3 = 6;
const int LED4 = 11;

// Servo object creation
Servo myServo;

// Distances in 4 areas
int dist1 = 0;
int dist2 = 0;
int dist3 = 0;
int dist4 = 0;

void setup() {
    myServo.attach(SERVO);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // Rotating servo in 4 positions
    dist1 = readDistance(15);
    analogWrite(LED1, dist1);
    delay(300);
    dist2 = readDistance(65);
    analogWrite(LED2, dist2);
    delay(300);
    dist3 = readDistance(115);
    analogWrite(LED3, dist3);
    delay(300);
    dist4 = readDistance(165);
    analogWrite(LED4, dist4);
    delay(300);
}

int readDistance(int pos) {
    myServo.write(pos);
    delay(600);
    int dist = analogRead(IR); // Reading data from sensor
    Serial.println(dist);
    
    // Translating values to needed range
    dist = map(dist, 3, 500, 0, 255);
    dist = constrain(dist, 0, 255);

    return dist;
}