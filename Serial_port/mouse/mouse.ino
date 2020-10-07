#include <Mouse.h>

const int LEFT_BUTTON = 4; // Left mouse button input
const int MIDDLE_BUTTON = 3; // Middle mouse button input
const int RIGHT_BUTTON = 2; // Right mouse button input
const int X_AXIS = 0; // Analog input 0 for joystick
const int Y_AXIS = 1; // Analog input 1 for joystick

void setup() {
    Mouse.begin();
}

void loop() {
    int xVal = readJoystick(X_AXIS);
    int yVal = readJoystick(Y_AXIS);

    Mouse.move(xVal, yVal, 0);

    readButton(LEFT_BUTTON, MOUSE_LEFT); // Reading left button state
    readButton(MIDDLE_BUTTON, MOUSE_MIDDLE); // Reafing middle button state
    readButton(RIGHT_BUTTON, MOUSE_RIGHT); // Reading right button state

    delay(5);
}

// Reading joystick values
int readJoystick(int axis) {
    int val = analogRead(axis); // Reading analog input
    val = map(val, 0, 1023, -10, 10); // Scaling the raw value

    if (val <= 2 && val >= -2) { // Get rid of mouse drift (blind zone)
        return 0;
    } else {
        return val;
    }
}

// Reading mouse state and sending mouse commands
void readButton(int pin, char mouseCommand) {
    // If button is pressed, emulating pressing, if it's not pressed yet
    if (digitalRead(pin) == HIGH) {
        if (!Mouse.isPressed(mouseCommand)) {
            Mouse.press(mouseCommand);
        }
    } else { // release mouse button
        if (Mouse.isPressed(mouseCommand)) {
            Mouse.release();
        }
    }
}