#include "pitches.h"

const int TRIGGER_PIN = A1;
const int SPEAKER = 9;

int notes[] = {
    NOTE_A4, NOTE_E3, NOTE_A4, 0,
    NOTE_A4, NOTE_E3, NOTE_A4, 0,
    NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B4,
    NOTE_A4, NOTE_B4, NOTE_C4, NOTE_D4,
    NOTE_E4, NOTE_E3, NOTE_A4, 0
};

int times[] = {
    250, 250, 250, 250,
    250, 250, 250, 250,
    125, 125, 125, 125,
    125, 125, 125, 125,
    250, 250, 250, 250,
};

void setup()
{
    // N/A
}

void loop()
{
    if (digitalRead(TRIGGER_PIN)) {
        for (int i = 0; i < 20; i++) {
            tone(SPEAKER, notes[i], times[i]);
            delay(times[i]);
        }
        // If button is pressed while playing, wait for tone to end
        while(digitalRead(TRIGGER_PIN));
    }
}