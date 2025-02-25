#include "LCDModule.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcdInit() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.print("Enter Password:");
    lcd.setCursor(0, 1);
}

void lcdShowMessage(const char* message) {
    lcd.clear();
    lcd.print(message);
}

void lcdShowPasswordChar(int position) {
    lcd.setCursor(position, 1);
    lcd.print('*');
}

void displayMessage(const char* line1, const char* line2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
}
