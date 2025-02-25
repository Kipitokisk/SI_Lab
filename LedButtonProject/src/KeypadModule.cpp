#include "KeypadModule.h"
#include "LCDModule.h"
#include "SerialIO.h"
#include <stdio.h>
#include <string.h>
#include "Led.h"

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
const char correctPassword[] = "1234";
char enteredPassword[5] = {0};
int passwordIndex = 0;
bool accessGranted = false;

void keypadInit() {
    memset(enteredPassword, 0, sizeof(enteredPassword));
}

char getKeyInput() {
    return keypad.getKey();
}

void handleKeyPress(char key, Led &led) {
    if (key >= '0' && key <= '9' && passwordIndex < 4) {
        enteredPassword[passwordIndex] = key;
        lcdShowPasswordChar(passwordIndex);
        passwordIndex++;

        if (passwordIndex == 4) {
            enteredPassword[4] = '\0';
            if (strcmp(enteredPassword, correctPassword) == 0) {
                accessGranted = true;
                led.turnOn();  // Use Led object instead of digitalWrite
                displayMessage("Access Granted!", "Type on/off");
                printf("\n=== Access Granted! ===\n");
            } else {
                accessGranted = false;
                for (int i = 0; i < 3; i++) {
                    led.turnOn();
                    delay(200);
                    led.turnOff();
                    delay(200);
                }
                displayMessage("Access Denied!", "");
                printf("\n=== Access Denied! ===\n");
                delay(2000);
                resetPassword(led);
            }
        }
    } else if (key == '*') {
        resetPassword(led);
    }
}

void resetPassword(Led &led) {
    passwordIndex = 0;
    memset(enteredPassword, 0, sizeof(enteredPassword));
    accessGranted = false;
    led.turnOff();
    displayMessage("Enter Password:", "");
}
