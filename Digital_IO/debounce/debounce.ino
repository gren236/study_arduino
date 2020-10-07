const int LED = 9; // LED connection PIN
const int BUTTON = 2; // BUTTON connection pin

boolean lastButton = LOW; // Init global var for saving last button state
boolean currentButton = LOW; // Init global var for current button state

boolean ledOn = false; // Current LED state (on/off)

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

/*
 * Debouncing function
 * receives the last button state as argument
 * and return the current one.
 */
boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON);
  if (last != current) { // State has changed
    delay(5);
    current = digitalRead(BUTTON);
    return current;    
  }
}

void loop() {
  currentButton = debounce(lastButton);
  
  if (lastButton == LOW && currentButton == HIGH) {
    ledOn = !ledOn;  
  }

  lastButton = currentButton;
  digitalWrite(LED, ledOn);
}
