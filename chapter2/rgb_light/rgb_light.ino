// Constants for parts pin numbers
const int BLED = 9;
const int GLED = 10;
const int RLED = 11;
const int BUTTON = 2;

boolean lastButton = LOW; // Last button state
boolean currentButton = LOW; // Current button state
int ledMode = 0; // RGB LED state

void setup() {
  pinMode(BLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
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

/**
 * Sets digital pins values as given.
 * r, g and b should be LOW or HIGH only!
 */
void setRGBDigital(int r, int g, int b) {
  digitalWrite(RLED, r);
  digitalWrite(GLED, g);
  digitalWrite(BLED, b);
}

/**
 * Sets pins values as given using PWM.
 * r, g and b should be from 0 to 255!
 */
void setRGBAnalog(int r, int g, int b) {
  analogWrite(RLED, r);
  analogWrite(GLED, g);
  analogWrite(BLED, b);
}

/**
 * Choosing LED mode.
 * Receives mode number and sets colors.
 */
void setMode(int mode) {
  switch (mode) {
    case 1: setRGBDigital(HIGH, LOW, LOW); break; // Red
    case 2: setRGBDigital(LOW, HIGH, LOW); break; // Green
    case 3: setRGBDigital(LOW, LOW, HIGH); break; // Blue
    case 4: setRGBAnalog(127, 0, 127); break; // Purple (Red + Blue)
    case 5: setRGBAnalog(0, 127, 127); break; // Turquoise (Blue + Green)
    case 6: setRGBAnalog(127, 127, 0); break; // Orange (Green + Red)
    case 7: setRGBAnalog(85, 85, 85); break; // White (Red + Green + Blue)
    default: setRGBDigital(LOW, LOW, LOW); break; // Turned off
  }
}

void loop() {
  currentButton = debounce(lastButton);

  if (lastButton == LOW && currentButton == HIGH) {
    ledMode++; // Increment RGB mode state
  }
  lastButton = currentButton;

  // If all modes are passed - reset back to 0
  if (ledMode == 8) ledMode = 0;

  setMode(ledMode);
}
