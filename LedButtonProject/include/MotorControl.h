#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

void setup_motor();

void setMotorPower(int power);

int getCurrentPower();

#endif