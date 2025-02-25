#ifndef KEYPAD_MODULE_H
#define KEYPAD_MODULE_H

#include <Arduino.h>
#include <Keypad.h>
#include "Led.h"

void keypadInit();
char getKeyInput();
void handleKeyPress(char key, Led &led);  // Led will be recognized here
void resetPassword(Led &led);  // Led will be recognized here

#endif
