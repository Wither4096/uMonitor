#include "SensorReadings.h"
#include <Arduino.h> //Required for NaN checking

// void SensorReadings::setHum(float hum){ hum_=hum; }
// void SensorReadings::setTempDHT(float tempDHT){ tempDHT_=tempDHT; }
// void SensorReadings::setTempLM35(float tempLM35){ tempLM35_=tempLM35; }
// void SensorReadings::setgas(float gas){ gas_=gas; }
// void SensorReadings::setlight(float light){ light_=light; }

SensorReadings::SensorReadings()
:
humidity_(0), temperatureDHT_(0), temperatureLM35_(0), airQuality_(0), light_(0)
{};

void SensorReadings::updateValues(float humidity, float temperatureDHT, float temperatureLM35, float airQuality, float light){
  humidity_=humidity;
  temperatureDHT_=temperatureDHT;
  temperatureLM35_=temperatureLM35;
  airQuality_=airQuality;
  light_=light;
}

//Getters
float SensorReadings::getHumidity()const{ return humidity_; }

float SensorReadings::getTemperatureDHT()const{ return temperatureDHT_; }

float SensorReadings::getTemperatureLM35()const{ return temperatureLM35_; }

float SensorReadings::getAverageTemperature()const{
  if(!isnan(temperatureDHT_))
    return (temperatureDHT_+temperatureLM35_)/2;
  else
    return temperatureLM35_;
}

float SensorReadings::getAirQuality()const{ return airQuality_; }

float SensorReadings::getLight()const{ return light_; }