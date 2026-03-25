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
  float voltage=(raw/4095.0)*5.0;
  float weightedValue=voltage*10.0;
  return weightedValue;
}

float SensorManager::readMQ135_(){
  int raw=analogRead(mqPin_);
  int mappedValue=raw/40.95;
  return mappedValue;
}

float SensorManager::readLight_(){
  int raw=analogRead(lightPin_);
  float mappedValue=raw/40.95; //maps the light value out of 100.00
  return mappedValue;
}

//void SensorManager::init() { dht_.begin(); };
void SensorManager::updateReadings(SensorReadings &readings){
  float humidity=dht_.readHumidity();
  float temperatureDHT=dht_.readTemperature();
  float temperatureLM35=readLM35_();
  float airQuality=readMQ135_();
  float light=readLight_();
  readings.updateValues(humidity,temperatureDHT,temperatureLM35,airQuality,light);
}