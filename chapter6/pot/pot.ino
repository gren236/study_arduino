const int POT = 0; // Connecting potentiometer to analog pin A0

void setup() {
    Serial.begin(9600); // Init serial port interface at speed 9600
}

void loop() {
    int val = analogRead(POT); // Reading from A0
    int per = map(val, 0, 1023, 0, 100); // Translating to percent

    Serial.print("Analog Reading: ");
    Serial.println(val); // Raw value output

    Serial.print(" Percentage: ");
    Serial.print(per); // Percentage value output
    Serial.println("%");

    delay(1000); // Waiting 1 second before receiving new portion of data
}