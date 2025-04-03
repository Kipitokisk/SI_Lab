#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

#define TRIG_PIN 9  
#define ECHO_PIN 10  


void ultrasonicInit();
float getDistance();

#endif