const int RLED = 11; // Red light pin
const int LIGHT = 0; // Analog pin for light sensor

const int BUTTON = 2; // Button pin to control light color

// Light level boundaries
const int MIN_LIGHT = 80;
const int MAX_LIGHT = 900;

int val = 0; // Current light level storage

void setup() {
  pinMode(RLED, OUTPUT);
  pinMode(BUTTON, INPUT);
  
  Serial.begin(9600);
}

void debugSerial(int value) {
  Serial.println(value);
  delay(500);
}

void loop() {
  // debugSerial(digitalRead(BUTTON));
  
  val = analogRead(LIGHT); // Get current light level

  val = map(val, MIN_LIGHT, MAX_LIGHT, 255, 0);
  val = constrain(val, 0, 255);
  analogWrite(RLED, val);
}
