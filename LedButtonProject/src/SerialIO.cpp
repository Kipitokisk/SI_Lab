#include "SerialIO.h"

int serial_putchar(char c, FILE* f) {
    Serial.write(c);
    return c;
}

int serial_getchar(FILE* f) {
    while (!Serial.available());
    return Serial.read();
}

FILE serial_stdout;

void serialInit() {
    Serial.begin(115200);
    while (!Serial);

    fdev_setup_stream(&serial_stdout, serial_putchar, serial_getchar, _FDEV_SETUP_WRITE);
    stdout = &serial_stdout;
    stdin = &serial_stdout;
}

void printRawDistance(float distance) {
    char buffer[10];
    dtostrf(distance, 5, 2, buffer);
    printf("Distance: %s cm\n", buffer);
}

void printSPDistance(float distance) {
    char buffer[10];
    dtostrf(distance, 5, 2, buffer);
    printf("Filtered distance: %s cm\n", buffer);
}

void printWADistance(float distance) {
    char buffer[10];
    dtostrf(distance, 5, 2, buffer);
    printf("Weighted average: %s cm\n", buffer);
}

