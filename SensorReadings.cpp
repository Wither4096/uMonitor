#include "SensorReadings.h"

SensorReadings::SensorReadings()
:
humidity_(0), temperatureDHT_(0), temperatureLM35_(0), airQuality_(0), light_(0)
{};

SensorReadings::SensorReadings(float humidity, float temperatureDHT, float temperatureLM35, float airQuality, float light)
:
humidity_(humidity), temperatureDHT_(temperatureDHT), temperatureLM35_(temperatureLM35), airQuality_(airQuality_), light_(light)
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
  bool dhtValid=!isnan(temperatureDHT_);
  bool lm35Valid=!(temperatureLM35_<-10||temperatureLM35_>80);
  if(dhtValid&&lm35Valid){
    return (temperatureLM35_+temperatureDHT_)/2;
  }
  else if(dhtValid&&!lm35Valid){
    return temperatureDHT_;
  }
  else if(!dhtValid&&lm35Valid){
    return temperatureLM35_;
  }
  else{
    return NAN;
  }
}

float SensorReadings::getAirQuality()const{ return airQuality_; }

float SensorReadings::getLight()const{ return light_; }