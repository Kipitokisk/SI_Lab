#ifndef SERIAL_IO_H
#define SERIAL_IO_H

#include <Arduino.h>
#include <stdio.h>

void serialInit();
void printRawDistance(float distance);
void printSPDistance(float distance);
void printWADistance(float distance);

#endif 
