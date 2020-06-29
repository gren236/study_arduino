const int LED = 9; // Led pin number
const int BUTTON = 2; // Button pin number

void setup() {
  pinMode(LED, OUTPUT); // Set led pin as output
  pinMode(BUTTON, INPUT); // Set button pin as input
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, HIGH);
  }
}
