#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

class PIDController {
private:
  // PID parameters
  float _kp;        // Proportional gain
  float _ki;        // Integral gain
  float _kd;        // Derivative gain
  
  // Control variables
  float _setPoint;  // Target value
  float _lastError; // Last error for derivative calculation
  float _integral;  // Integral sum
  float _output;    // Controller output (0-255 for PWM)
  
  // Timing
  unsigned long _lastTime;    // Last calculation time
  unsigned long _sampleTime;  // Sample interval in milliseconds

  // Output limits
  float _outMin;    // Minimum output limit
  float _outMax;    // Maximum output limit

public:
  PIDController(float kp, float ki, float kd, unsigned long sampleTime = 100);
  
  // Initialize controller
  void begin(float setPoint);
  
  // Calculate new output value based on input
  float compute(float input);
  
  // Setter methods
  void setTunings(float kp, float ki, float kd);
  void setSampleTime(unsigned long sampleTime);
  void setOutputLimits(float min, float max);
  void setSetPoint(float setPoint);
  
  // Getter methods
  float getSetPoint();
  float getOutput();
  void getTunings(float *kp, float *ki, float *kd);
};

#endif // PID_CONTROLLER_H