#ifndef SERIAL_MANAGER_H
#define SERIAL_MANAGER_H

#include "PIDController.h"

class SerialManager {
private:
  char _buffer[20];        // Command buffer
  int _bufferIndex;        // Current position in buffer
  unsigned long _lastSendTime;  // Last data transmission time
  unsigned long _sendInterval;  // Data transmission interval
  
public:
  SerialManager(unsigned long sendInterval = 200);
  
  void begin(unsigned long baudRate);
  
  // Process incoming serial commands
  void processCommands(PIDController &pid);
  
  // Send data formatted for Serial Plotter
  void sendPlotterData(float setPoint, float temperature, float output);
  
  // Display welcome message and instructions
  void showWelcomeMessage();
  
  // Output current PID parameters
  void showPIDParameters(PIDController &pid);
};

#endif // SERIAL_MANAGER_H