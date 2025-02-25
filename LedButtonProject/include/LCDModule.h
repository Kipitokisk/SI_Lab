#ifndef LCD_MODULE_H
#define LCD_MODULE_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

void lcdInit();
void lcdShowMessage(const char* message);
void lcdShowPasswordChar(int position);
void lcdClear();
void displayMessage(const char* line1, const char* line2);

#endif // LCD_MODULE_H
