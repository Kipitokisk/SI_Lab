#include "SerialIO.h"
#include "MotorControl.h"
#include "CommandProcessor.h"


void setup() {
    serialInit();
    setup_motor();
    printCommandHelp();
}

void loop() {
    if (Serial.available() > 0) {
        readLine();
      }
      delay(10);
}

