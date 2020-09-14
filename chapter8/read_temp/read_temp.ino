#include <Wire.h>

int temp_address = 72; // I2C temp device address: 1001000

void setup() {
    Serial.begin(9600);
    // Creating Wire object
    Wire.begin();
}

void loop() {
    // Sending request
    // Choosing the device sending device address
    Wire.beginTransmission(temp_address);
    // Setting asking bit to 0 for reading
    Wire.write(0);
    // Sending stop bit
    Wire.endTransmission();

    // Reading the device temperature
    // Get 1 byte with device address
    Wire.requestFrom(temp_address, 1);
    // Waiting for a response
    while (Wire.available() == 0);
    // Reading data to a variable
    int c = Wire.read();
    // Converting from C to F
    int f = round(c * 9.0 / 5.0 + 32.0);
    // Sending temperature value to serial port
    Serial.print(c);
    Serial.print("C ");
    Serial.print(f);
    Serial.println("F");

    delay(500);
}