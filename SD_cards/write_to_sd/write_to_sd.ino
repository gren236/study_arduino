#include <SD.h>

// These pins are set by SD lib
// MOSI = 11
// MISO = 12
// SCLK = 13

const int CS_PIN = 10;

void setup()
{
    Serial.begin(9600);

    Serial.println("Initializing card");
    pinMode(CS_PIN, OUTPUT);
    if (!SD.begin()) {
        Serial.println("Card failure");
        return;
    }
    Serial.println("Card ready");
}

void loop()
{
    long timeStamp = millis();
    String dataString = "Hello There!";

    File dataFile = SD.open("log.csv", FILE_WRITE);
    if (dataFile) {
        dataFile.print(timeStamp);
        dataFile.print(",");
        dataFile.println(dataString);
        dataFile.close();

        // Same data for debugging
        Serial.print(timeStamp);
        Serial.print(",");
        Serial.println(dataString);
    } else {
        Serial.println("File stream open failure");
    }
    delay(5000);
}