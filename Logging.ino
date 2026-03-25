#ifdef LOGGING
void serialLogDataPoints(){
  Serial.println("---START LOG---");
  
  Serial.print("Humidity: ");Serial.print(readings.getHumidity());Serial.println("%");


  Serial.print("Temperature (DHT11): ");Serial.print(readings.getTemperatureDHT());Serial.println("\xC2\xB0");


  Serial.print("Temperature (LM35): ");Serial.print(readings.getTemperatureLM35());Serial.println("\xC2\xB0");


  Serial.print("Temperature (Average): ");Serial.print(readings.getAverageTemperature());Serial.println("\xC2\xB0");


  Serial.print("Light Intensity : ");Serial.println(readings.getLight());


  Serial.print("Relative AQI: ");Serial.println(readings.getAirQuality());

  


  Serial.println("---END LOG---");Serial.println();
  delay(500);
};
#endif