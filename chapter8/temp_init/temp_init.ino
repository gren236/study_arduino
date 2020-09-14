/**
 * Reading temperature from I2C sensor
 * showing it on LED gistogram
 * and sending to Serial reader program
 */
#include <Wire.h>

const int SER = 8; // DATA pin
const int RCLK = 9; // LATCH pin
const int SRCLK = 10; // CLOCK pin

int temp_address = 72; // Address of TMP sensor (1001000)

int vals[8] = {1,3,7,15,31,63,127,255}; // LED values

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    pinMode(SER, OUTPUT);
    pinMode(RCLK, OUTPUT);
    pinMode(SRCLK, OUTPUT);
}

void loop()
{
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

    // Mapping temp for LED indicator
    int graph = map(c, 24, 32, 0, 7);
    graph = constrain(graph, 0, 7);

    digitalWrite(RCLK, LOW); // Starting write to shift register
    shiftOut(SER, SRCLK, MSBFIRST, vals[graph]);
    digitalWrite(RCLK, HIGH); // Stop writing, send to outputs

    // Converting from C to F
    int f = round(c * 9.0 / 5.0 + 32.0);
    // Sending temperature value to serial port
    Serial.print(c);
    Serial.print("C,");
    Serial.print(f);
    Serial.println("F.");

    delay(500);
}