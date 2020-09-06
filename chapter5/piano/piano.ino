#define NOTE_C  262 //Hz
#define NOTE_D  294 //Hz
#define NOTE_E  330 //Hz
#define NOTE_G  392 //Hz
#define NOTE_A  440 //Hz

const int SPEAKER = 9; // Speaker pin

// Button pins
const int BUTTON_C = 7;
const int BUTTON_D = 6;
const int BUTTON_G = 5;
const int BUTTON_E = 4;
const int BUTTON_A = 3;

void setup() {
    // No setup needed    
}

void loop() {
    while (digitalRead(BUTTON_C))
        tone(SPEAKER, NOTE_C);
    while (digitalRead(BUTTON_D))
        tone(SPEAKER, NOTE_D);
    while (digitalRead(BUTTON_G))
        tone(SPEAKER, NOTE_G);
    while (digitalRead(BUTTON_E))
        tone(SPEAKER, NOTE_E);
    while (digitalRead(BUTTON_A))
        tone(SPEAKER, NOTE_A);

    // Stop playing if all buttons released
    noTone(SPEAKER);
}