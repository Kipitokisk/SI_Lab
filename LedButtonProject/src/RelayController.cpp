#include "RelayController.h"
#include <Arduino.h>

RelayController::RelayController(int pin) 
  : _pin(pin), _state(false), _pwmMode(false), _pwmValue(0),
    _pwmPeriod(1000), _lastPwmTime(0), _onTime(0) {}

void RelayController::begin() {
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
}

void RelayController::update(float temp, float setPoint, float hysteresis) {
  // Only use this if not in PWM mode
  if (_pwmMode) return;
  
  if (temp < (setPoint - hysteresis)) {
    _state = true;
  } else if (temp > (setPoint + hysteresis)) {
    _state = false;
  }
  digitalWrite(_pin, _state);
}

void RelayController::updatePWM(float controlOutput) {
  // Only use this if in PWM mode
  if (!_pwmMode) return;
  
  // Store PWM value (0-255)
  _pwmValue = constrain(controlOutput, 0, 255);
  
  // Calculate ON time within period
  _onTime = (_pwmValue / 255.0) * _pwmPeriod;
  
  // Implement software PWM
  unsigned long now = millis();
  unsigned long elapsedTime = now - _lastPwmTime;
  
  // Reset cycle if period elapsed
  if (elapsedTime >= _pwmPeriod) {
    _lastPwmTime = now;
    elapsedTime = 0;
  }
  
  // Set output based on position in cycle
  if (elapsedTime < _onTime) {
    digitalWrite(_pin, HIGH);
    _state = true;
  } else {
    digitalWrite(_pin, LOW);
    _state = false;
  }
}

void RelayController::setPWMMode(bool pwmMode) {
  _pwmMode = pwmMode;
  
  // Reset state when changing modes
  _state = false;
  digitalWrite(_pin, LOW);
  _lastPwmTime = millis();
}

void RelayController::setPWMPeriod(unsigned long period) {
  _pwmPeriod = period;
}

bool RelayController::isOn() {
  return _state;
}

float RelayController::getPWMValue() {
  return _pwmValue;
}