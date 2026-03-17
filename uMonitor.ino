#include <DHT.h>
//#define RZERO -10

const int analogMQPin=25;
const int digitalMQPin=33;
const int dhtPin=32;
const int buzzer=15;

DHT dhtSens(dhtPin,DHT11);

float hum=0;
float tempu=0;
float analogMQVal=0;
float digitalMQVal=0;
float mappedMQVal=0;

void setup() {
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  dhtSens.begin();
}

void loop() {
  hum=dhtSens.readHumidity();
  tempu=dhtSens.readTemperature();
  analogMQVal=analogRead(analogMQPin);
  digitalMQVal=digitalRead(digitalMQPin);
  mappedMQVal=map(analogMQVal,0,4095,0,1023);
  alertAir(mappedMQVal);
  serialLogDataPoints();
}

void serialLogDataPoints(){
  Serial.println("---START LOG---");
  Serial.println("HUM/TEMP: ");
  Serial.print("Humidity: ");Serial.println(hum);
  delay(500);
  Serial.print("Temperature: ");Serial.println(tempu);
  delay(500);
  Serial.print("PPM: ");Serial.println(mappedMQVal);
  delay(1000);
  Serial.println("---END LOG---");
};

void alertAir(int ppm){
  if(ppm>=800)
    tone(buzzer,880,500);
  else if(ppm>=700)
    tone(buzzer,440,250);
}