const int POT = 0;
int val;

void setup() {
    Serial.begin(9600);
}

void loop() {
    val = map(analogRead(POT), 0, 1023, 0, 255);

    Serial.println(val);
    delay(50);
}