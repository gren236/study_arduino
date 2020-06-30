const int RLED = 11; // Red light pin
const int LIGHT = 0; // Analog pin for light sensor

// Light level boundaries
const int MIN_LIGHT = 80;
const int MAX_LIGHT = 900;

int val = 0; // Current light level storage

void setup() {
  pinMode(RLED, OUTPUT);
}

void loop() {
  val = analogRead(LIGHT); // Get current light level

  val = map(val, MIN_LIGHT, MAX_LIGHT, 255, 0);
  val = constrain(val, 0, 255);
  analogWrite(RLED, val);
}
