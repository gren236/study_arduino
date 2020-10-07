#include <MPU6050.h>
#include <Wire.h>

// Accel vars
MPU6050 accel;
int16_t ax, ay, az; // Accel values
int16_t gx, gy, gz; // Gyro values

// LED pins
const int RED_PIN = 6;
const int GREEN_PIN = 5;

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    accel.initialize();
    accel.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);

    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);

    delay(100);
}

void loop()
{
    accel.getAcceleration(&ax, &ay, &az);

    Serial.print("Z (raw): "); Serial.print(az);
    Serial.print("\tZ (actual): "); Serial.println((float(az) / 32768.0) * 2.0);

    if (az < 0) {
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);
    } else {
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);
    }

    delay(100);
}