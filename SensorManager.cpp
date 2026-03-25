#include "SensorManager.h"

SensorManager::SensorManager(int dhtPin, int dhtType, int lm35pin, int mqPin, int lightPin)
:
dht_(dhtPin,dhtType),
mqPin_(mqPin),
lm35Pin_(lm35pin),
lightPin_(lightPin)
{
  dht_.begin();
};

float SensorManager::readLM35_(){
  float raw=analogRead(lm35Pin_);
  float voltage=(raw/ADC_MAX)*3.3;
  float weightedValue=voltage*16.0; // Calibration based on testing @ room temperature
  return weightedValue;
}

float SensorManager::readMQ135_(){
  float raw=analogRead(mqPin_);
  float mappedValue=raw/ADC_MAX*100.0;
  return mappedValue;
}

float SensorManager::readLight_(){
  float raw=analogRead(lightPin_);
  float mappedValue=raw/ADC_MAX*100.0; //maps the light value out of 100.00
  return mappedValue;
}

void SensorManager::updateReadings(SensorReadings &readings){
  float humidity=dht_.readHumidity();
  float temperatureDHT=dht_.readTemperature();
  float temperatureLM35=readLM35_();
  float airQuality=readMQ135_();
  float light=readLight_();
  readings.updateValues(humidity,temperatureDHT,temperatureLM35,airQuality,light);
}