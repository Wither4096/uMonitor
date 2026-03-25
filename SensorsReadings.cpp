#include "SensorReadings.h"
// void SensorReadings::setHum(float hum){
//   hum_=hum;
// }
// void SensorReadings::setTempDHT(float tempDHT){
//   tempDHT_=tempDHT;
// }
// 
// void SensorReadings::setTempLM35(float tempLM35){
//   tempLM35_=tempLM35;
// }
// 
// void SensorReadings::setgas(float gas){
//   gas_=gas;
// }
// 
// void SensorReadings::setLightVal(float lightVal){
//   lightVal_=lightVal;
// }

void SensorReadings::updateValues(float hum, float tempDHT, float tempLM35, float gas, float lightVal){
  hum_=hum;
  tempDHT_=tempDHT;
  tempLM35_=tempLM35;
  gas_=gas;
  lightVal_=lightVal;
}

//Getters
float SensorReadings::getHum()const{
  return hum_;
}

float SensorReadings::getTempDHT()const{
  return tempDHT_;
}

float SensorReadings::getTempLM35()const{
  return tempLM35_;
}

float SensorReadings::getTempAvg()const{
  return (tempDHT_+tempLM35_)/2;
}

float SensorReadings::getGas()const{
  return gas_;
}

float SensorReadings::getLight()const{
  return lightVal_;
}

SensorReadings::SensorReadings()
:
hum_(0), tempDHT_(0), tempLM35_(0), gas_(0), lightVal_(0)
{}