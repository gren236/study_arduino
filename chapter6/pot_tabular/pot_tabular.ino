const int POT = 0; // Connecting potentiometer to analog pin A0

void setup() {
    Serial.begin(9600); // Init serial port interface at speed 9600
}

void loop() {
    Serial.println("\nAnalog Pin\tRaw Value\tPercentage");
    Serial.println("-------------------------------------------");

    for (int i = 0; i < 10; i++)  {
        int val = analogRead(POT); // Reading from A0
        int per = map(val, 0, 1023, 0, 100); // Translating to percent

        Serial.print("A0\t\t");
        Serial.print(val);
        Serial.print("\t\t");
        Serial.print(per);
        Serial.println("%");

        delay(1000);
    }
}