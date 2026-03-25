#pragma once
class SensorReadings{
  private:
  float hum_;
  float tempuDHT_;
  float tempuLM35_;
  float mqVal_;
  float lightVal_;
  public:

  //Setters
  void setHum(float hum);
  void setTempDHT(float tempuDHT);
  void setTempLM35(float tempuLM35);
  void setMQVal(float mqVal);
  void setLightVal(float lightVal);

  //Getters
  float getHum();
  float getTempDHT();
  float getTempLM35();
  float getTempAvg();
  float getGas();
  float getLight();

  SensorReadings();
};