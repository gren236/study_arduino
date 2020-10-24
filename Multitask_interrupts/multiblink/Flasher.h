#ifndef Flasher_h
#define Flasher_h

class Flasher
{
    int ledPin;     // the number of led pin
    long blinkTime; // Time in ms between switching on/off

    int ledState;                 // LED state (HIGH/LOW)
    unsigned long previousMillis; // Last time led was updated

public:
    Flasher(int pin, long blink);
    void Update();
};

#endif