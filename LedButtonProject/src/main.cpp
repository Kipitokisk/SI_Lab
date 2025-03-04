#include <Arduino.h>
#include "Button.h"
#include "LED.h"
#include "SerialIO.h"

// Button objects for task 1 and task 3
Button button1(4);  
Button button2(3);  
Button button3(2); 

// LED objects for task 1 and task 2
Led led1(13);  
Led led2(11);  

// Global variables
volatile bool led1State = false;  
volatile int blinkCount = 0;     
volatile bool led2State = false;  

// Task 1: Button LED
void taskButtonLED() {
    if (button1.isPressed()) {
        led1State = !led1State;  
        if (led1State) {
            led1.turnOn();
        } else {
            led1.turnOff();
        }
    }
}

void taskLEDIntermittent() {
    static unsigned long previousMillis = 0;

    if (!led1State && blinkCount > 0) {
        unsigned long currentMillis = millis();
        int blinkRate = max(50, 1000 / blinkCount);  

        if (currentMillis - previousMillis >= blinkRate) {
            previousMillis = currentMillis;
            led2State = !led2State;  
            led2.toggle();
        }
    } else {
        led2.turnOff();  
    }
}




// Task 3: Variable State (Increment/Decrement)
void taskVariableState() {
    if (button2.isPressed()) {
        blinkCount++;  
    } else if (button3.isPressed()) {
        blinkCount--;  
    }
}

// Idle Task: Reporting System State
void taskIdle() {
    printf("LED 1 State: %s\n", led1State ? "ON" : "OFF");
    printf("LED 2 Blink Count: %d\n", blinkCount);
    delay(200); 
}

void setup() {
    serialInit();

    led1.turnOff();
    led2.turnOff();
}

void loop() {
    taskButtonLED();         // Task 1: Button LED
    taskLEDIntermittent();   // Task 2: LED Intermittent
    taskVariableState();     // Task 3: Variable State
    taskIdle();              // Idle Task: Reporting state
}

