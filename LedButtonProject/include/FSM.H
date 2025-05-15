#ifndef FSM_H
#define FSM_H
#include "Led.h"

// State definitions
typedef enum {
    STATE_OFF,
    STATE_ON
} FSM_State;

// Function prototypes
void fsm_init(Led* led);
void fsm_transition(void);
void fsm_update(void);
FSM_State fsm_get_state(void);

#endif