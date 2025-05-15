#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
private:
    uint8_t pin;
    unsigned long debounceDelay;
    unsigned long lastDebounceTime;
    int lastStableState;
    int lastReading;
    bool isPressedFlag;

public:
    Button(uint8_t pin, unsigned long debounceDelay = 50);
    bool isPressed(); // returns true only on press event
};

#endif
