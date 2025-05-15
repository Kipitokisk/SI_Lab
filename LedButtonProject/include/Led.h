#ifndef LED_H
#define LED_H
#include <Arduino.h>

class Led {
private:
    uint8_t pin;
    bool state;

public:
    Led(uint8_t pin);
    void toggle();
    void turnOn();
    void turnOff();
};

#endif