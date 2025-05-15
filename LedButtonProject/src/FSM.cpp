#include "fsm.h"

// Static variables
static FSM_State current_state = STATE_OFF;
static Led* led;

void fsm_init(Led* led_ptr) {
    led = led_ptr;
    current_state = STATE_OFF;
    led->turnOff();
    Serial.println("FSM Initialized: OFF");
}

void fsm_transition(void) {
    // Toggle between states
    Serial.println("fsm_transition CALLED");
    switch (current_state) {
        case STATE_OFF:
            current_state = STATE_ON;
            Serial.println("Transition: OFF -> ON");
            break;
        case STATE_ON:
            current_state = STATE_OFF;
            Serial.println("Transition: ON -> OFF");
            break;
    }
}

void fsm_update(void) {
    // Update LED based on current state
    switch (current_state) {
        case STATE_OFF:
            led->turnOff();
            break;
        case STATE_ON:
            led->turnOn();
            break;
    }
}

FSM_State fsm_get_state(void) {
    return current_state;
}