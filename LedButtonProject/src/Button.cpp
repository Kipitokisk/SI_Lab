#include "Button.h"

Button::Button(uint8_t pin, unsigned long debounceDelay)
    : pin(pin), debounceDelay(debounceDelay), lastDebounceTime(0),
      lastStableState(LOW), lastReading(LOW), isPressedFlag(false) {
    pinMode(pin, INPUT); // or INPUT_PULLUP if using internal pull-up
}

bool Button::isPressed() {
    int reading = digitalRead(pin);

    // If reading changed, reset debounce timer
    if (reading != lastReading) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        // If the reading is stable and changed from previous stable state
        if (reading != lastStableState) {
            lastStableState = reading;

            if (reading == HIGH) {
                Serial.println("Button Press Detected");
                return true; // Only return true on rising edge
            }
        }
    }

    lastReading = reading;
    return false;
}
