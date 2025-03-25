#include "UltrasonicSensor.h"

void ultrasonicInit() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

float getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(50);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(100);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    return duration * 0.034 / 2; 
}
