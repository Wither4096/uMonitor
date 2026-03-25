#include "SensorReadings.h"
void SensorReadings::setHum(float hum){
  hum_=hum;
}

void SensorReadings::setTempDHT(float tempuDHT){
  tempuDHT_=tempuDHT;
}

void SensorReadings::setTempLM35(float tempuLM35){
  tempuLM35_=tempuLM35;
}

void SensorReadings::setMQVal(float mqVal){
  mqVal_=mqVal;
}

void SensorReadings::setLightVal(float lightVal){
  lightVal_=lightVal;
}

//Getters
float SensorReadings::getHum(){
  return hum_;
}

float SensorReadings::getTempDHT(){
  return tempuDHT_;
}

float SensorReadings::getTempLM35(){
  return tempuLM35_;
}

float SensorReadings::getTempAvg(){
  return (tempuDHT_+tempuLM35_)/2;
}

float SensorReadings::getGas(){
  return mqVal_;
}

float SensorReadings::getLight(){
  return lightVal_;
}

SensorReadings::SensorReadings(){
hum_=0;
tempuDHT_=0;
tempuLM35_=0;
mqVal_=0;
lightVal_=0;
}