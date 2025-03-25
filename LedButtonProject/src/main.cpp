#include <Arduino.h>
#include "Arduino_FreeRTOS.h"
#include "task.h"
#include "UltrasonicSensor.h"
#include "SerialIO.h"

void ultrasonicTask(void *pvParameters) {    
  TickType_t xLastWakeTime = xTaskGetTickCount(); 
  for (;;) { 
    float distance = getDistance(); 
    printDistance(distance);
    if (distance < 20.0) {         
      printf("ALERT: TOO CLOSE!!!\n"); 
    } 
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(500)); 
  } 
} 


void setup() {
    serialInit();
    ultrasonicInit();
    xTaskCreate(ultrasonicTask, "Ultrasonic", 128, NULL, 1, NULL);
}

void loop() {
}
