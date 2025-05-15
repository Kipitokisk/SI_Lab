#include "ButtonManager.h"
#include <Arduino.h>

ButtonManager::ButtonManager(int upPin, int downPin)
  : _upPin(upPin), _downPin(downPin), _handled(false), 
    _lastPressTime(0), _valueChanged(false) {}

void ButtonManager::begin() {
  pinMode(_upPin, INPUT_PULLUP);
  pinMode(_downPin, INPUT_PULLUP);
}

void ButtonManager::update(float &setPoint) {
  unsigned long now = millis();
  
  // Reset valueChanged flag
  _valueChanged = false;

  if (!_handled && (digitalRead(_upPin) == LOW || digitalRead(_downPin) == LOW)) {
    if (digitalRead(_upPin) == LOW) {
      setPoint += 0.5;
      _valueChanged = true;
    }
    else if (digitalRead(_downPin) == LOW) {
      setPoint -= 0.5;
      _valueChanged = true;
    }

    _handled = true;
    _lastPressTime = now;
  }

  if (_handled && now - _lastPressTime >= _cooldown) {
    if (digitalRead(_upPin) == HIGH && digitalRead(_downPin) == HIGH) {
      _handled = false;
    }
  }
}

bool ButtonManager::wasPressed() {
  return _valueChanged;
}