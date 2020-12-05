// D0 pin of receiver
const int TRIGGER_PIN = A1;

// Built-in LED
const int LED_PIN = 13;

// Store pressing time
unsigned long start_time;

// Store if button is pressed
boolean announced;

void setup()
{
    Serial.begin(9600);
    Serial.println("RF Test");
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    digitalWrite(LED_PIN, LOW);
    announced = false;

    // Iterate over loop if button is pressed
    while (digitalRead(TRIGGER_PIN))
    {
        if (!announced)
        {
            start_time = millis();
            Serial.print("PRESSED... ");
            announced = true;
        }
        digitalWrite(LED_PIN, HIGH);
    }

    // After button is released, calculate pressing time
    if (announced) {
        Serial.print("RELEASED after ");
        unsigned long duration = millis() - start_time;
        Serial.print(round(duration/1000.0)); // Convert to seconds

        Serial.println(" second(s).");
    }
}