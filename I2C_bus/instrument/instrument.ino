#include <MPU6050.h>
#include <Wire.h>

// Accel vars
MPU6050 accel;
int16_t ax, ay, az; // Accel values
int16_t gx, gy, gz; // Gyro values

// LED pins
const int RED_PIN = 6;
const int GREEN_PIN = 5;
const int BLUE_PIN = 3;

const int SPEAKER = 9; // Speaker pin

const int ACCEL_THRESHOLD = 5000;

// Pentatone scale C D E G A
#define NOTE_C  262 // Hz
#define NOTE_D  294 // Hz
#define NOTE_E  330 // Hz
#define NOTE_G  392 // Hz
#define NOTE_A  440 // Hz
#define NOTE_C2 523 // Hz

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    accel.initialize();
    accel.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);

    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    delay(100);
}

void loop()
{
    accel.getAcceleration(&ax, &ay, &az);

    // Remove 1 G from Z (Earth acceleration)
    az = az - 16384;

    Serial.print(ax);
    Serial.print(" ");
    Serial.print(ay);
    Serial.print(" ");
    Serial.println(az);

    // Play note if threshold is passed (for 100 ms)
    if (ax < -ACCEL_THRESHOLD) tone(SPEAKER, NOTE_C, 100);
    if (ax > ACCEL_THRESHOLD) tone(SPEAKER, NOTE_D, 100);
    if (ay < -ACCEL_THRESHOLD) tone(SPEAKER, NOTE_E, 100);
    if (ay > ACCEL_THRESHOLD) tone(SPEAKER, NOTE_G, 100);
    if (az < -ACCEL_THRESHOLD) tone(SPEAKER, NOTE_A, 100);
    if (az > ACCEL_THRESHOLD) tone(SPEAKER, NOTE_C2, 100);

    // Turn LED on proportional to acceleration
    analogWrite(RED_PIN, constrain(map(abs(ax), ACCEL_THRESHOLD, 20000, 0, 255), 0, 255));
    analogWrite(GREEN_PIN, constrain(map(abs(ay), ACCEL_THRESHOLD, 20000, 0, 255), 0, 255));
    analogWrite(BLUE_PIN, constrain(map(abs(az), ACCEL_THRESHOLD, 20000, 0, 255), 0, 255));
}