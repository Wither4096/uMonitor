#pragma once
#include <DHT.h>
#include "SensorReadings.h"

constexpr float ADC_MAX = 4095.0;

class SensorManager{
  private:

  DHT dht_;
  int lm35Pin_;
  int mqPin_;
  int lightPin_;
  float readLM35_();
  float readMQ135_();
  float readLight_();

  public:

  SensorManager(int dhtPin, int dhtType, int lm35pin, int mqPin, int lightPin);
  void updateReadings(SensorReadings& readings);
  SensorReadings update();
};