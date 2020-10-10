#include <TimerOne.h>

const int BTN = 2;
const int SPEAKER = 12;

// Music keys
#define NOTE_C 65
#define NOTE_D 73
#define NOTE_E 82
#define NOTE_F 87
#define NOTE_G 98
#define NOTE_A 110
#define NOTE_B 123

// Volatile vars to be modified by interrupts
volatile int key = NOTE_C;
volatile int octave_multiplier = 1;

void setup()
{
    Serial.begin(9600);

    pinMode(SPEAKER, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(BTN), changeKey, RISING);

    // Timer-based interrupts
    Timer1.initialize(500000);
    Timer1.attachInterrupt(changePitch);
}

void changeKey()
{
    octave_multiplier = 1;
    if (key == NOTE_C) {
        key = NOTE_D;
    } else if (key == NOTE_D) {
        key = NOTE_E;
    } else if (key == NOTE_E) {
        key = NOTE_F;
    } else if (key == NOTE_F) {
        key = NOTE_G;
    } else if (key == NOTE_G) {
        key = NOTE_A;
    } else if (key == NOTE_A) {
        key = NOTE_B;
    } else if (key == NOTE_B) {
        key = NOTE_C;
    }
}

void changePitch() {
    octave_multiplier = octave_multiplier * 2;
    if (octave_multiplier > 16) {
        octave_multiplier = 1;
    }
    tone(SPEAKER, key * octave_multiplier);
}

void loop()
{
    Serial.print("Key: ");
    Serial.print(key);
    Serial.print(" Multiplier: ");
    Serial.print(octave_multiplier);
    Serial.print(" Frequency: ");
    Serial.println(key * octave_multiplier);
    delay(100);
}