#pragma once
class SensorReadings{
  private:
  float humidity_;
  float temperatureDHT_;
  float temperatureLM35_;
  float airQuality_;
  float light_;
  public:

  //Setters
  // void setHum(float hum);
  // void setTempDHT(float tempDHT);
  // void setTempLM35(float tempLM35);
  // void setgas(float gas);
  // void setlight(float light);
  void updateValues(float hum, float tempDHT,float tempLM35, float gas, float light);

  //Getters
  float getHumidity()const;
  float getTemperatureDHT()const;
  float getTemperatureLM35()const;
  float getAverageTemperature()const;
  float getAirQuality()const;
  float getLight()const;

  SensorReadings();
};