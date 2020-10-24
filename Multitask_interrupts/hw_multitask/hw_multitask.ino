const int BTN = 2; // Button pin
// LED pins
const int RED = 11;
const int GREEN = 10;
const int BLUE = 9;

// Volatile vars can be changed from interrupt funcs
volatile int selectedLED = RED;

void setup()
{
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);

    // pin signal is inverted, so we expect RISING
    attachInterrupt(digitalPinToInterrupt(BTN), swap, RISING);

    Serial.begin(9600);
}

void swap() {
    Serial.println("Interrupted!");
    // Turn off current LED
    digitalWrite(selectedLED, LOW);

    // Turn on other LED
    if (selectedLED == GREEN) {
        selectedLED = RED;
    } else if (selectedLED == RED) {
        selectedLED = BLUE;
    } else if (selectedLED == BLUE) {
        selectedLED = GREEN;
    }
}

void loop()
{
    //Ramp Brightness Up
    for (int i=255; i>=0; i--)
    {
        analogWrite(selectedLED, i);
        delay(10);
    }

    //Ramp Brightness Down
    for (int i=0; i<=255; i++)
    {
        analogWrite(selectedLED, i);
        delay(10);
    }
    delay(1000);
}