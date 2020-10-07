#include <LiquidCrystal.h>

int time = 0; // Starting time value
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // LCD display object

void setup()
{
    lcd.begin(16, 2);
    lcd.print("Gren's Display");  
}

void loop()
{
    // Set cursor to second line
    lcd.setCursor(0, 1);
    // Output time value
    lcd.print(time);
    // Pause for 1 second
    delay(1000);
    // Increment counter value
    time++;
}