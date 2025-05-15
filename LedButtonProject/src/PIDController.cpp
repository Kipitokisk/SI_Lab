#include "PIDController.h"
#include <Arduino.h>

PIDController::PIDController(float kp, float ki, float kd, unsigned long sampleTime)
  : _kp(kp), _ki(ki), _kd(kd), 
    _setPoint(0), _lastError(0), _integral(0), _output(0),
    _lastTime(0), _sampleTime(sampleTime),
    _outMin(0), _outMax(255) {
}

void PIDController::begin(float setPoint) {
  _setPoint = setPoint;
  _lastError = 0;
  _integral = 0;
  _output = 0;
  _lastTime = millis();
}

float PIDController::compute(float input) {
  unsigned long now = millis();
  unsigned long timeChange = now - _lastTime;
  
  // Only compute if the sample interval has passed
  if (timeChange >= _sampleTime) {
    // Calculate error
    float error = _setPoint - input;
    
    // Calculate P term
    float pTerm = _kp * error;
    
    // Calculate I term
    _integral += error * (timeChange / 1000.0);
    
    // Prevent integral windup
    if (_integral > _outMax / _ki) {
      _integral = _outMax / _ki;
    } else if (_integral < _outMin / _ki) {
      _integral = _outMin / _ki;
    }
    
    float iTerm = _ki * _integral;
    
    // Calculate D term
    float dInput = (error - _lastError) / (timeChange / 1000.0);
    float dTerm = _kd * dInput;
    
    // Remember for next time
    _lastError = error;
    _lastTime = now;
    
    // Compute output
    _output = pTerm + iTerm + dTerm;
    
    // Constrain output to limits
    if (_output > _outMax) {
      _output = _outMax;
    } else if (_output < _outMin) {
      _output = _outMin;
    }
  }
  
  return _output;
}

void PIDController::setTunings(float kp, float ki, float kd) {
  // Ensure tunings are positive
  if (kp < 0 || ki < 0 || kd < 0) return;
  
  _kp = kp;
  _ki = ki;
  _kd = kd;
}

void PIDController::setSampleTime(unsigned long sampleTime) {
  if (sampleTime > 0) {
    float ratio = (float)sampleTime / (float)_sampleTime;
    _ki *= ratio;
    _kd /= ratio;
    _sampleTime = sampleTime;
  }
}

void PIDController::setOutputLimits(float min, float max) {
  if (min >= max) return;
  
  _outMin = min;
  _outMax = max;
  
  // Adjust output if outside limits
  if (_output > _outMax) {
    _output = _outMax;
  } else if (_output < _outMin) {
    _output = _outMin;
  }
  
  // Adjust integral term to prevent windup
  if (_integral > _outMax / _ki) {
    _integral = _outMax / _ki;
  } else if (_integral < _outMin / _ki) {
    _integral = _outMin / _ki;
  }
}

void PIDController::setSetPoint(float setPoint) {
  _setPoint = setPoint;
}

float PIDController::getSetPoint() {
  return _setPoint;
}

float PIDController::getOutput() {
  return _output;
}

void PIDController::getTunings(float *kp, float *ki, float *kd) {
  *kp = _kp;
  *ki = _ki;
  *kd = _kd;
}