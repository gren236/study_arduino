#include <Keyboard.h>

const int LIGHT = 1; // Light sensor
const int THRESHOLD = 160; // Value to start locking from

void setup() {
    Keyboard.begin();
}

void loop() {
    int brightness = analogRead(LIGHT);

    if (brightness < THRESHOLD) {
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('l');

        delay(100);

        Keyboard.releaseAll();
    }
}