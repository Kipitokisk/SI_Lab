#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

#define TRIG_PIN 12  
#define ECHO_PIN 13  

void ultrasonicInit();
float getDistance();

#endif