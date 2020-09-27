#include <LiquidCrystal.h>

int time = 0; // Starting time value
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // LCD display object

// Creating arrays for progress bar
byte p20[8] {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
};

byte p40[8] {
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
};

byte p60[8] {
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
};

byte p80[8] {
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
};

byte p100[8] {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
};

void setup()
{
    lcd.begin(16, 2);
    lcd.print("Gren's Display");

    // Defining custom chars
    lcd.createChar(0, p20);
    lcd.createChar(1, p40);
    lcd.createChar(2, p60);
    lcd.createChar(3, p80);
    lcd.createChar(4, p100);
}

void loop()
{
    // Set cursor to second line
    lcd.setCursor(0, 1);
    // Clear second line (16 spaces)
    lcd.print("                ");
    
    // Iterate every symbol
    for(int i = 0; i < 16; i++){
        // Iterate every char value (p20-p100)
        for(int j = 0; j < 5; j++){
            lcd.setCursor(i, 1); // Set column (symbol matrix)
            lcd.write(j); // Output custom symbol by ID
            delay(100);
        }
    }
}