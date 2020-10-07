const int POT = 0; // Analog inpot 0 for potentiometer connection
int val = 0; // Potentiometer value storage

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(POT);
  Serial.println(val);
  delay(500);
}
