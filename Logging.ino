void serialLogDataPoints(){
  Serial.println("---START LOG---");
  
  Serial.print("Humidity: ");Serial.print(vars.getHum());Serial.println("%");
  Serial.print("Temperature (DHT11): ");Serial.print(vars.getTempDHT());Serial.println("\xC2\xB0");
  Serial.print("Temperature (LM35): ");Serial.print(vars.getTempLM35());Serial.println("\xC2\xB0");
  Serial.print("Temperature (Average): ");Serial.print(vars.getTempAvg());Serial.println("\xC2\xB0");
  Serial.print("Light Intensity : ");Serial.println(vars.getLight());
  Serial.print("Raw MQ135: ");Serial.println(vars.getGas());
  Serial.print("Mapped MQ135: ");Serial.println(map(vars.getGas(),0,4095,0,1023));
  
  Serial.println("---END LOG---");
  Serial.println();
  delay(500);
};