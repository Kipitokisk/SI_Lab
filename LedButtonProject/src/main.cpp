#include "Button.h"
#include "fsm.h"
#include "Led.h"

// Pin definitions
#define BUTTON_PIN 2
#define LED_PIN 13

// Create objects
Led led(LED_PIN);
Button button(BUTTON_PIN);

// Redirect printf to Serial
int serial_putc(char c, FILE* f) {
    Serial.write(c);
    return c;
}

FILE serial_stdout;

void setup() {
    // Initialize Serial
    Serial.begin(9600);
    fdev_setup_stream(&serial_stdout, serial_putc, NULL, _FDEV_SETUP_WRITE);
    stdout = &serial_stdout;

    printf("FSM LED Control Started\n");

    // Initialize FSM
    fsm_init(&led);
}

void loop() {
    if (button.isPressed()) {
        printf("Calling fsm_transition()\n");
        fsm_transition();
    }

    fsm_update();

    printf("Current State: %s\n", fsm_get_state() == STATE_OFF ? "OFF" : "ON");

    delay(100); // Debounce-friendly delay
}
