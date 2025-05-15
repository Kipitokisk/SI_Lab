#ifndef RELAY_CONTROLLER_H
#define RELAY_CONTROLLER_H

class RelayController {
private:
  int _pin;            // Output pin connected to relay/MOSFET
  bool _state;         // Current state
  bool _pwmMode;       // Whether to use PWM or ON/OFF control
  float _pwmValue;     // Current PWM value (0-255)
  unsigned long _pwmPeriod;    // PWM period in milliseconds
  unsigned long _lastPwmTime;  // Last PWM update time
  unsigned long _onTime;       // Time relay should be ON in PWM cycle
  
public:
  RelayController(int pin);
  
  void begin();
  
  // Simple ON/OFF control
  void update(float temp, float setPoint, float hysteresis);
  
  // PWM-based control (simulating analog output with digital relay)
  void updatePWM(float controlOutput);
  
  // Set mode (true for PWM, false for ON/OFF)
  void setPWMMode(bool pwmMode);
  
  // Set PWM cycle period in milliseconds (default: 1000ms)
  void setPWMPeriod(unsigned long period);
  
  // Is relay currently on
  bool isOn();
  
  // Get current PWM value (0-255)
  float getPWMValue();
};

#endif // RELAY_CONTROLLER_H