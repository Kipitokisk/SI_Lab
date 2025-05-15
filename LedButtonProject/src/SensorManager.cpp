#include "SensorManager.h"
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void SensorManager::begin() {
  dht.begin();
}

float SensorManager::readTemperature() {
  return dht.readTemperature();
}
