void setup()
{
    Serial.begin(9600);
    digitalWrite(13, OUTPUT);
}

void loop()
{
    int val = digitalRead(A1);
    digitalWrite(13, val);
    Serial.println(val);
    delay(50);
}