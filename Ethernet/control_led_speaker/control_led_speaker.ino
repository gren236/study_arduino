#include <Ethernet.h>
#include <SPI.h>
#include "server_form.h"

const int RED = 7;
const int GREEN = 6;
const int BLUE = 5;
const int SPEAKER = 3;

int freq = 0;
int pin;
int pinOutput = LOW;
// int pinOutput = LOW;

// MAC address of ethernet device
byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0x4A, 0xE0};

// Server on port 80
EthernetServer server = EthernetServer(80);
boolean receiving = false; // GET data

void setup()
{
    Serial.begin(9600);
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);

    // Connecting to DHCP
    if (!Ethernet.begin(mac))
    {
        Serial.println("Could not configure server with DHCP");
        return;
    }
    else
    {
        Serial.println("Ethernet Configured!");
    }

    // Launch Server
    server.begin();
    Serial.print("Server started.\nLocal IP: ");
    Serial.println(Ethernet.localIP());
}

void loop()
{
    digitalWrite(pin, pinOutput);

    EthernetClient client = server.available();
    if (client)
    {
        // Request is ended with an empty line
        boolean currentLineIsBlank = true;
        boolean sentHeader = false;

        while (client.connected())
        {
            if (client.available())
            {
                char c = client.read(); // Reading from buffer
                if (receiving && c == ' ')
                {
                    receiving = false; // End transmitting
                }
                if (c == '?')
                    receiving = true; // Looking for ? symbol
                // Waiting for GET data
                if (receiving)
                {
                    if (c == 'L')
                    {
                        Serial.print("Toggling Pin ");
                        pin = client.parseInt();
                        Serial.println(pin);
                        pinOutput = invert(pinOutput);
                        digitalWrite(pin, pinOutput);
                    }
                    else if (c == 'S')
                    {
                        Serial.print("setting Frequency to ");
                        freq = client.parseInt();
                        Serial.println(freq);
                        if (freq == 0)
                        {
                            noTone(SPEAKER);
                        }
                        else
                        {
                            tone(SPEAKER, freq);
                        }
                    }
                    // Code for additional devices goes here
                }

                if (!sentHeader)
                {
                    client.println("HTTP/1.1 200 OK");
                    client.println();
                    client.println(HTML_SERVER_FORM);
                    sentHeader = true;
                }

                if (c == '\n' && currentLineIsBlank) break;

                if (c == '\n')
                {
                    currentLineIsBlank = true;
                }
                else if (c != '\r')
                {
                    currentLineIsBlank = false;
                }
            }
        }
        delay(5); // Give some time to browser to get data
        client.stop();
    }
}

int invert(int signal) {
    if (signal == HIGH) {
        return LOW;
    }
    return HIGH;
}