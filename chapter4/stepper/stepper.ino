#include <Stepper.h>

// Stepper motor constants
const int STEPS_PER_REV = 2048; // 2048 steps per revolution

// Pins to control H-bridge
const int COIL1_MC1 = 2;
const int COIL1_MC2 = 3;
const int COIL2_MC1 = 4;
const int COIL2_MC2 = 5;

// Init Servo lib
Stepper myStepper(STEPS_PER_REV, COIL1_MC1, COIL1_MC2, COIL2_MC1, COIL2_MC2);

void setup()
{
    myStepper.setSpeed(20); // 20 revolutions per minute
}

void loop()
{
    // 1 revolution in one direction
    myStepper.step(STEPS_PER_REV);
    delay(500);
    // 1 revolution in another direction
    myStepper.step(-STEPS_PER_REV);
    delay(500);
}