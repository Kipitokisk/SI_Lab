#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <Arduino.h>
#include <stdio.h>

void processCommand(const char* command);

void readLine();

void printCommandHelp();

#endif 