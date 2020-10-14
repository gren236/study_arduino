#define RTC_CHIP_IS_DS1307
// #define FORCE_UPDATE

#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

// These pins are set by SD lib
// MOSI = 11
// MISO = 12
// SCLK = 13

const int CS_PIN = 10;

const int IR_PIN = 0; // IR sensor A0

// Use compiler flags to set actual rtc chip
#ifdef RTC_CHIP_IS_DS1307
RTC_DS1307 RTC;
String chip = "DS1307";
#else
RTC_PCF8523 RTC;
String chip = "PCF8532";
#endif

#ifdef FORCE_UPDATE
bool update_clock = true;
#else
bool update_clock = false;
#endif

String time, date;
// Init distance vars
int raw = 0;
int raw_prev = 0;
boolean active = false;
int update_time = 0;

void updateDateTime() {
    DateTime datetime = RTC.now();
    String year = String(datetime.year(), DEC);
    String month = String(datetime.month(), DEC);
    String day = String(datetime.day(), DEC);
    String hour = String(datetime.hour(), DEC);
    String minute = String(datetime.minute(), DEC);
    String second = String(datetime.second(), DEC);

    // Form a human string
    date = year + "/" + month + "/" + day;
    time = hour + ":" + minute + ":" + second;
}

void setup() {
    Serial.begin(9600);
    pinMode(CS_PIN, OUTPUT);

    RTC.begin();

    #ifdef RTC_CHIP_IS_DS1307
    if (!RTC.isrunning()) update_clock = true;
    #else
    if (!RTC.initialized()) update_clock = true;
    #endif

    // If RTC is not working, set the current compile time
    if (update_clock) {
        Serial.print(F("Setting "));
        Serial.print(chip);
        Serial.print(F(" time to compile time..."));
        RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
        Serial.println(F("Done!"));
    } else {
        Serial.print(chip);
        Serial.println(F(" time is already set!"));
    }

    // Output time values
    updateDateTime();
    Serial.println(F("RTC Date: "));
    Serial.print(date);
    Serial.print(F("RTC time: "));
    Serial.println(time);

    // Init SD card
    Serial.println(F("Initializing card..."));
    if (!SD.begin()) {
        Serial.println(F("Card failure"));
        return;
    }
    Serial.println(F("Card ready"));

    // Write CSV headers to file
    File dataFile = SD.open("log.csv", FILE_WRITE);
    if (dataFile) {
        dataFile.println(F("\nNew log started!"));
        dataFile.println(F("Date,Time,Raw,Active"));
        dataFile.close();

        // Same data for debugging
        Serial.println(F("\nNew log started!"));
        Serial.println(F("Date,Time,Raw,Active"));
    } else {
        Serial.println(F("File stream open failure"));
        while(1);
    }
}

void loop() {
    updateDateTime();
    
    // Get movement data
    raw = analogRead(IR_PIN);
    // If current value is larger than previous one by 75, detect a movement
    if (abs(raw - raw_prev) > 75)
        active = true;
    else
        active = false;
    raw_prev = raw;

    // Open a file and write to it
    if (active || update_time == 20) {
        File dataFile = SD.open("log.csv", FILE_WRITE);
        if (dataFile) {
            dataFile.print(date);
            dataFile.print(F(","));
            dataFile.print(time);
            dataFile.print(F(","));
            dataFile.print(raw);
            dataFile.print(F(","));
            dataFile.println(active);
            dataFile.close(); // Data is written only when file is closed!

            // Same data for debugging
            Serial.print(date);
            Serial.print(F(","));
            Serial.print(time);
            Serial.print(F(","));
            Serial.print(raw);
            Serial.print(F(","));
            Serial.println(active);
        } else {
            Serial.println(F("File stream open failure"));
        }
        update_time = 0;
    }

    delay(50);
    update_time++;
}