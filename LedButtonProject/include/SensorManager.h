#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

class SensorManager {
  public:
    void begin();
    float readTemperature();
};

#endif
