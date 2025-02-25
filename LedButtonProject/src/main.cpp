#include <Arduino.h>
#include "SerialIO.h"
#include "KeypadModule.h"
#include "LCDModule.h"
#include "CommandHandler.h"
#include "Led.h"

#define LED_PIN 13

Led led(LED_PIN);

void setup() {
    serialInit();
    lcdInit();
    keypadInit();
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void loop() {
    char key = getKeyInput();
    if (key) {
        handleKeyPress(key, led);
    }

    if (Serial.available() > 0) {
        processSerialInput();
    }
}
