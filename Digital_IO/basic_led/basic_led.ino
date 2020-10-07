const int LED=9; // Number of LED pin

void setup() {
  pinMode(LED, OUTPUT); // Set up LED pin as output
}

void loop() {
  for (int i = 100; i <= 1000; i = i + 100) {
    digitalWrite(LED, HIGH); // Set HIGH voltage for this output
    delay(i);
    digitalWrite(LED, LOW); // Set LOW voltage for this output
    delay(i);
  }
}
