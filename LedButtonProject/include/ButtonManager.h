#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

class ButtonManager {
private:
  int _upPin;          // Pin for UP button
  int _downPin;        // Pin for DOWN button
  bool _handled;       // Flag to handle button debouncing
  unsigned long _lastPressTime;  // Time of last button press
  const unsigned long _cooldown = 300;  // Cooldown period in milliseconds
  bool _valueChanged;  // Flag indicating if value was changed
  
public:
  ButtonManager(int upPin, int downPin);
  
  void begin();
  
  // Update setpoint based on button presses
  void update(float &setPoint);
  
  // Check if value was changed in the last update
  bool wasPressed();
};

#endif // BUTTON_MANAGER_H