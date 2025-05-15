#include "SerialManager.h"
#include <Arduino.h>

SerialManager::SerialManager(unsigned long sendInterval)
  : _bufferIndex(0), _lastSendTime(0), _sendInterval(sendInterval) {
  memset(_buffer, 0, sizeof(_buffer));
}

void SerialManager::begin(unsigned long baudRate) {
  Serial.begin(baudRate);
  while (!Serial && millis() < 3000);  // Wait for serial with timeout
}

void SerialManager::processCommands(PIDController &pid) {
  while (Serial.available() > 0) {
    char c = Serial.read();
    
    // Process command on newline or carriage return
    if (c == '\n' || c == '\r') {
      if (_bufferIndex > 0) {
        // Null-terminate buffer
        _buffer[_bufferIndex] = '\0';
        
        // Process command
        char command = _buffer[0];
        float value = 0.0;
        
        // Extract value if present
        if (_bufferIndex > 1) {
          value = atof(&_buffer[1]);
        }
        
        // Handle commands
        switch (command) {
          case 's': // Set setpoint
            pid.setSetPoint(value);
            Serial.print(F("Setpoint changed to: "));
            Serial.println(pid.getSetPoint());
            break;
            
          case 'p': // Set P gain
            {
              float kp, ki, kd;
              pid.getTunings(&kp, &ki, &kd);
              pid.setTunings(value, ki, kd);
              Serial.print(F("P value changed to: "));
              Serial.println(value);
            }
            break;
            
          case 'i': // Set I gain
            {
              float kp, ki, kd;
              pid.getTunings(&kp, &ki, &kd);
              pid.setTunings(kp, value, kd);
              Serial.print(F("I value changed to: "));
              Serial.println(value);
            }
            break;
            
          case 'd': // Set D gain
            {
              float kp, ki, kd;
              pid.getTunings(&kp, &ki, &kd);
              pid.setTunings(kp, ki, value);
              Serial.print(F("D value changed to: "));
              Serial.println(value);
            }
            break;
            
          case 'h': // Show help
            showWelcomeMessage();
            break;
            
          default:
            Serial.println(F("Unknown command. Type 'h' for help."));
            break;
        }
        
        // Reset buffer
        memset(_buffer, 0, sizeof(_buffer));
        _bufferIndex = 0;
      }
    } 
    // Add character to buffer if not control character
    else if (c >= 32 && c <= 126) {
      if (_bufferIndex < sizeof(_buffer) - 1) {
        _buffer[_bufferIndex++] = c;
      }
    }
  }
}

void SerialManager::sendPlotterData(float setPoint, float temperature, float output) {
  unsigned long now = millis();
  
  // Send data at specified interval
  if (now - _lastSendTime >= _sendInterval) {
    _lastSendTime = now;
    
    // Format for Arduino Serial Plotter: SetPoint,Temperature,Output
    Serial.print(setPoint);
    Serial.print(",");
    Serial.print(temperature);
    Serial.print(",");
    Serial.println(output);
  }
}

void SerialManager::showWelcomeMessage() {
  Serial.println(F("\n=== PID Temperature Control System ==="));
  Serial.println(F("\nCommands:"));
  Serial.println(F("  s<value> - Set temperature setpoint"));
  Serial.println(F("  p<value> - Set P gain"));
  Serial.println(F("  i<value> - Set I gain"));
  Serial.println(F("  d<value> - Set D gain"));
  Serial.println(F("  h - Show this help message"));
  Serial.println(F("\nPlotter data format: SetPoint,Temperature,Output"));
  Serial.println(F("=========================================\n"));
}

void SerialManager::showPIDParameters(PIDController &pid) {
  float kp, ki, kd;
  pid.getTunings(&kp, &ki, &kd);
  
  Serial.print(F("Current setpoint: "));
  Serial.println(pid.getSetPoint());
  Serial.print(F("PID parameters: P="));
  Serial.print(kp);
  Serial.print(F(" I="));
  Serial.print(ki);
  Serial.print(F(" D="));
  Serial.println(kd);
  Serial.println();
}