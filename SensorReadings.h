#pragma once
class SensorReadings{
  private:
  float hum_;
  float tempDHT_;
  float tempLM35_;
  float gas_;
  float lightVal_;
  public:

  //Setters
  // void setHum(float hum);
  // void setTempDHT(float tempDHT);
  // void setTempLM35(float tempLM35);
  // void setgas(float gas);
  // void setLightVal(float lightVal);
  void updateValues(float hum, float tempDHT,float tempLM35, float gas, float lightVal);

  //Getters
  float getHum()const;
  float getTempDHT()const;
  float getTempLM35()const;
  float getTempAvg()const;
  float getGas()const;
  float getLight()const;

  SensorReadings();
};