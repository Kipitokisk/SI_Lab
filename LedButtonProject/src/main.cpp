#include <Arduino.h>
#include "Button.h"
#include "Led.h"

#define BUTTON_PIN 2
#define LED_PIN 13

Button button(BUTTON_PIN);
Led led(LED_PIN);

int serial_putc(char c, FILE *stream) {
  Serial.write(c);
  return 0;
}

int serial_getc(FILE *stream) {
  while (!Serial.available()) {}
  return Serial.read();  
}

FILE serial_stdout;
FILE serial_stdin;

void setup() {
    Serial.begin(115200);
    led.turnOn();

    fdev_setup_stream(&serial_stdout, serial_putc, NULL, _FDEV_SETUP_WRITE);
    
    stdout = &serial_stdout;

    printf("System Ready! Send 'led on' or 'led off' to control the LED.\n");
}

void loop() {
  // int someDelay = random(10, 500);
  // led.toggle();
  // delay(someDelay);
  //   if (button.isPressed()) {
  //       led.toggle();
  //       delay(200); // Debounce
  //   }
  char command[10];

    if (Serial.available() > 0) {
        printf("Enter command: ");
        Serial.readBytesUntil('\n', command, sizeof(command) - 1);
        command[strcspn(command, "\r\n")] = 0;

        if (strcmp(command, "led on") == 0) {
            led.turnOn();
            printf("LED is now ON\n");
        } 
        else if (strcmp(command, "led off") == 0) {
            led.turnOff();
            printf("LED is now OFF\n");
        } 
        else {
            printf("Invalid command! Use 'led on' or 'led off'.\n");
        }
    }
}
