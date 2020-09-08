#include <Keyboard.h>

const int TEMP = 0; // A0 (TMP36)
const int LIGHT = 1; // A1 (Photoresistor)
const int RLED = 3; // LED pin 3
const int BUTTON = 2; // Button on pin 2

boolean lastButton = LOW; // Last button state
boolean currentButton = LOW; // Current button state
boolean running = false; // CSV write is turned off by default
int counter = 1; // Writing data index

void setup() {
  pinMode(RLED, OUTPUT);
  Keyboard.begin(); // Enable keyboard emulation
}

void loop() {
  currentButton = debounce(lastButton); // Get button state
  if (lastButton == LOW && currentButton == HIGH) { // If it's pressed...
    running = !running; // Switch writing state
  }
  lastButton = currentButton; // Set button state

  if (running) { // If writing is on...
    digitalWrite(RLED, HIGH); // Turn on the LED

    if (millis() % 1000 == 0) { // If 1 sec passed...
      int temperature = analogRead(TEMP); // Read tmp from sensor
      int brightness = analogRead(LIGHT); // Read brightness from resistor

      Keyboard.print(counter); // Write data index
      Keyboard.print(",");
      Keyboard.print(temperature); // Write temperature value
      Keyboard.print(",");
      Keyboard.println(brightness); // Write brightness value and \n

      counter++; // Increment index
    } else {
      digitalWrite(RLED, LOW); // Turn off the LED
    }
  }
}

/*
 * Function to prevent button fuzzing
 */
boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON); // Reading button state
  if (last != current) { // If something changed...
    delay(5); // Wait for 5 ms
    current = digitalRead(BUTTON); // Read button state
  }
  return current;
}
