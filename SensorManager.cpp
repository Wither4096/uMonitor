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
  double weightedValue = 0;
  for(int i=0; i < SAMPLES ; i++){
    float raw = analogRead(lm35Pin_);
    float voltage = (raw / ADC_MAX) * 5.0;
    weightedValue += voltage * 16.0; // Calibration based on testing @ room temperature
  }
  return weightedValue / SAMPLES;
}

float SensorManager::readMQ135_(){
  double mappedValue = 0;
  for(int i=0; i < SAMPLES ; i++){
    float raw = analogRead(mqPin_);
    mappedValue += raw / ADC_MAX * 100.0;
  }
  mappedValue /= SAMPLES;
  return 100.0 - mappedValue;
}

float SensorManager::readLight_(){
  double mappedValue = 0;
  for(int i=0; i < SAMPLES ; i++){
    float raw = analogRead(lightPin_);
    mappedValue += raw / ADC_MAX * 100.0; //maps the light value out of 100.00
  }
  mappedValue /= SAMPLES;
  return 100.0 - mappedValue; //display from 0 to 100 instead of 100 to 0 (darkest to brightest)
}

float SensorManager::dhtAverageHumidity_(){
  int averageHumidity = 0;
  for(int i=0; i < SAMPLES ; i++) averageHumidity += dht_.readHumidity();
  return averageHumidity / SAMPLES;
}

float SensorManager::dhtAverageTemperature_(){
  int averageTemperature = 0;
  for(int i=0; i < SAMPLES ; i++) averageTemperature += dht_.readTemperature();
  return averageTemperature / SAMPLES;
}

void SensorManager::updateReadings(SensorReadings &readings){
  float humidity = dhtAverageHumidity_();
  float temperatureDHT = dhtAverageTemperature_();
  float temperatureLM35 = readLM35_();
  float airQuality = readMQ135_();
  float light = readLight_();
  readings.updateValues(humidity,temperatureDHT,temperatureLM35,airQuality,light);
}
SensorReadings SensorManager::update(){
  float humidity = dht_.readHumidity();
  float temperatureDHT = dht_.readTemperature();
  float temperatureLM35 = readLM35_();
  float airQuality = readMQ135_();
  float light = readLight_();
  return SensorReadings(humidity, temperatureDHT, temperatureLM35, airQuality, light);
}