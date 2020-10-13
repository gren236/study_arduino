#include <SD.h>

// These pins are set by SD lib
// MOSI = 11
// MISO = 12
// SCLK = 13

const int CS_PIN = 10;

int refresh_rate = 5000; // Default write refresh rate

void setup() {
    Serial.begin(9600);

    Serial.println("Initializing card");
    pinMode(CS_PIN, OUTPUT);
    if (!SD.begin()) {
        Serial.println("Card failure");
        return;
    }
    Serial.println("Card ready");

    // Reading refresh rate from SD card
    File commandFile = SD.open("speed.txt");
    if (commandFile) {
        Serial.println("Reading command file");

        while (commandFile.available() > 0) {
            int parsed = commandFile.parseInt();
            if (parsed > 0)
                refresh_rate = parsed;
        }
        Serial.print("Refresh rate = ");
        Serial.print(refresh_rate);
        Serial.println("ms");
        commandFile.close();
    } else {
        Serial.println("Could not read command file!");
        Serial.print("Will use default refresh rate of ");
        Serial.print(refresh_rate);
        Serial.println("ms!");
    }
}

void loop() {
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
    delay(refresh_rate);
}