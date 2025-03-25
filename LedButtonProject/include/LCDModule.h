#ifndef LCD_MODULE_H
#define LCD_MODULE_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>


void lcdInit();
void displayMessage(const char *line1, const char *line2);

#endif 