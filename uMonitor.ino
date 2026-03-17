#include <DHT.h>
//#define RZERO -10

const int analogMQPin=25;
const int digitalMQPin=33;
const int dhtPin=32;

DHT dhtSens(dhtPin,DHT11);

void setup() {
  Serial.begin(9600);
  dhtSens.begin();
}

void loop() {
  float hum=dhtSens.readHumidity();
  float tempu=dhtSens.readTemperature();
  float analogMQVal=analogRead(analogMQPin);
  float digitalMQVal=digitalRead(digitalMQPin);
  float mappedMQVal=map(analogMQVal,0,4095,0,1023);
  Serial.println("HUM/TEMP: ");
  Serial.print("Humidity: ");Serial.println(hum);
  delay(500);
  Serial.print("Temperature: ");Serial.println(tempu);
  delay(500);
  Serial.print("PPM: ");Serial.println(mappedMQVal);
  delay(1000);
}
