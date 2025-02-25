#include "CommandHandler.h"
#include "LCDModule.h"
#include <stdio.h>
#include <string.h>

char command[10];

void processSerialInput() {
    if (scanf("%s", command) == 1) {
        for (char *p = command; *p; p++) {
            *p = tolower(*p);
        }

        if (strcmp(command, "on") == 0 || strcmp(command, "off") == 0) {
            handleCommand(command);
        } else {
            printf("Invalid command! Use 'on' or 'off'\n");
        }
    }
}

void handleCommand(const char* cmd) {
    if (strcmp(cmd, "on") == 0) {
        digitalWrite(LED_BUILTIN, HIGH);
        displayMessage("LED Status:", "ON");
        printf("LED status: ON\n");
    } else if (strcmp(cmd, "off") == 0) {
        digitalWrite(LED_BUILTIN, LOW);
        displayMessage("LED Status:", "OFF");
        printf("LED status: OFF\n");
    }
}
