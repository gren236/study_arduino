#include <Stepper.h>

// Stepper motor constants
const int STEPS_PER_REV = 2048; // 2048 steps per revolution

// 60 seconds * 1000 ms / 2048 steps = 30 ms/step
const int MS_PER_STEP = 30;

// Pins to control H-bridge
const int COIL1_MC1 = 2;
const int COIL1_MC2 = 3;
const int COIL2_MC1 = 4;
const int COIL2_MC2 = 5;

// Button pins
const int START = 8;
const int STOP = 9;

// Init Servo lib
Stepper chronograph(STEPS_PER_REV, COIL1_MC1, COIL1_MC2, COIL2_MC1, COIL2_MC2);

// State variables
unsigned long last_time = 0;
unsigned long curr_time = 0;
int steps_taken = 0;

void setup()
{
    chronograph.setSpeed(14);

    // Enable pull-up resistors for buttons
    pinMode(START, INPUT_PULLUP);
    pinMode(STOP, INPUT_PULLUP);
}

void loop()
{
    while (digitalRead(START) == HIGH); // Wait for start button to be pushed

    last_time = millis();
    
    // Do while until minute has passed
    while (digitalRead(STOP) == HIGH && steps_taken < STEPS_PER_REV) {
        curr_time = millis();

        if (curr_time - last_time >= MS_PER_STEP) {
            chronograph.step(1);
            steps_taken++;

            last_time = curr_time;
        }
    }

    // Stop button pressed or one minute passed

    if (steps_taken < STEPS_PER_REV) { // Return chronograph to initial state
        chronograph.step(-steps_taken);
    }

    steps_taken = 0;
}