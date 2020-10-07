#include <Wire.h>
#define TEMP_ADDR 72

#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // LCD display object

// Degree symbol
byte degree[8] {
    B00110,
    B01001,
    B01001,
    B00110,
    B00000,
    B00000,
    B00000,
    B00000,
};

// "Fan on" symbol
byte fan_on[8] {
    B00100,
    B10101,
    B01110,
    B11111,
    B01110,
    B10101,
    B00100,
    B00000,
};

// "Fan off" symbol
byte fan_off[8] {
    B00100,
    B00100,
    B00100,
    B11111,
    B00100,
    B00100,
    B00100,
    B00000,
};

// Buttons
const int DOWN_BUTTON = 9;
const int UP_BUTTON = 10;

boolean lastDownTempButton = LOW;
boolean currentDownTempButton = LOW;
boolean lastUpTempButton = LOW;
boolean currentUpTempButton = LOW;

int set_temp = 23; // Temp threshold value

const int SPEAKER = 8; // Speaker pin
boolean one_time = false; // Sound flag

const int FAN = 11; // Fan pin

void setup()
{
    pinMode(FAN, OUTPUT);

    Wire.begin();

    // LCD display settings
    lcd.begin(16, 2);
    
    lcd.createChar(0, degree);
    lcd.createChar(1, fan_off);
    lcd.createChar(2, fan_on);

    // Static chars
    // Line 1
    lcd.setCursor(0, 0);
    lcd.print("Current:");
    lcd.setCursor(10, 0);
    lcd.write((byte)0);
    lcd.setCursor(11, 0);
    lcd.print("C");
    // Line 2
    lcd.setCursor(0, 1);
    lcd.print("Set:");
    lcd.setCursor(10, 1);
    lcd.write((byte)0);
    lcd.setCursor(11, 1);
    lcd.print("C");
    lcd.setCursor(15, 1);
    lcd.write(1);
}

void loop()
{
    //Get the Temperature
    Wire.beginTransmission(TEMP_ADDR); //Start talking
    Wire.write(0);                     //Ask for register zero
    Wire.endTransmission();            //Complete transmission
    Wire.requestFrom(TEMP_ADDR, 1);    //Request 1 byte
    while(Wire.available() == 0);      //Wait for response
    int c = Wire.read();               //Get the temp in C
    lcd.setCursor(8,0);                //Move the cursor
    lcd.print(c);                      //Print this new value

    // Read and debounce buttons
    currentDownTempButton = debounce(lastDownTempButton, DOWN_BUTTON);
    currentUpTempButton = debounce(lastUpTempButton, UP_BUTTON);
    // Decrease set temp value
    if (lastDownTempButton == LOW && currentDownTempButton == HIGH) {
        set_temp--;
    } else if (lastUpTempButton == LOW && currentUpTempButton == HIGH) {
        set_temp++;
    }
    // Output set temp value to LCD
    lcd.setCursor(8, 1);
    lcd.print(set_temp);
    // Change last button values
    lastDownTempButton = currentDownTempButton;
    lastUpTempButton = currentUpTempButton;

    // It's hot!
    if (c >= set_temp) {
        // Make a sound
        if (!one_time) {
            tone(SPEAKER, 400);
            delay(500);
            one_time = true;
        } else {
            noTone(SPEAKER);
        }
        // Turn on fan and LCD symbol
        digitalWrite(FAN, HIGH);
        lcd.setCursor(15, 1);
        lcd.write(2);
    } else { // It's cold!
        // Turn off speaker
        // Reset one_time to false
        // Turn off the fan
        noTone(SPEAKER);
        one_time = false;
        digitalWrite(FAN, LOW);
        lcd.setCursor(15, 1);
        lcd.write(1);
    }
}

boolean debounce(boolean last, int pin) {
    boolean current = digitalRead(pin);
    if (last != current) {
        delay(5);
        current = digitalRead(pin);
    }
    return current;
}