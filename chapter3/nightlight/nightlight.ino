const int RLED = 11; // Red light pin
const int GLED = 10; // Green light pin
const int BLED = 9;  // Blue light pin

const int BUTTON = 2; // Button pin

const int LIGHT = 0; // Analog pin for light sensor

const int BUTTON = 2; // Button pin to control light color

// Light level boundaries
const int MIN_LIGHT = 80;
const int MAX_LIGHT = 900;

int val = 0; // Current light level storage

boolean lastButton = LOW; // Last button state
boolean currentButton = LOW; // Current button state
int ledMode = 0; // Current LED color mode

void setup() { 
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON);

  if (current != last) {
    delay(5);
    current = digitalRead(BUTTON);
  }
  return current;
}

void loop() {
  // Get light value
  val = analogRead(LIGHT); // Get current light level

  val = map(val, MIN_LIGHT, MAX_LIGHT, 255, 0);
  val = constrain(val, 0, 255);

  // Get button value
  currentButton = debounce(lastButton);

  if (lastButton == LOW && currentButton == HIGH) {
    ledMode++; // Increment RGB mode state
  }
  lastButton = currentButton;

  // If all modes are passed - reset back to 0
  if (ledMode == 3) ledMode = 0;

  // Set current light color from mode
  if (ledMode == 0) {
    analogWrite(RLED, val);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
  } else if (ledMode == 1) {
    digitalWrite(RLED, LOW);
    analogWrite(GLED, val);
    digitalWrite(BLED, LOW);
  } else {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    analogWrite(BLED, val);
  }
}
