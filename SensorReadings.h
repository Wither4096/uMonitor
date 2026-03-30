#pragma once
#include <Arduino.h> //Required for NaN checking
class SensorReadings{
  private:
  float humidity_;
  float temperatureDHT_;
  float temperatureLM35_;
  float airQuality_;
  float light_;
  public:

  //Setters
  void updateValues(float hum, float tempDHT,float tempLM35, float airQuality, float light);

  //Getters
  float getHumidity()const;
  float getTemperatureDHT()const;
  float getTemperatureLM35()const;
  float getAverageTemperature()const;
  float getAirQuality()const;
  float getLight()const;

  SensorReadings();
};