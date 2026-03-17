#include <DHT.h>
//#define RZERO -10

const int analogMQPin=34;
//const int digitalMQPin=33;
const int dhtPin=33;
const int buzzer=15;

DHT dhtSens(dhtPin,DHT11);

float hum=0;
float tempu=0;
float analogMQVal=0;
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
  mappedMQVal=map(analogMQVal,0,4095,0,1023);
  alertAir(mappedMQVal);
  serialLogDataPoints();
}

void serialLogDataPoints(){
  Serial.println("---START LOG---");
  Serial.print("Humidity: ");Serial.println(hum);
  Serial.print("Temperature: ");Serial.println(tempu);
  Serial.print("Raw MQ135: ");Serial.println(analogMQVal);
  Serial.print("Mapped MQ135: ");Serial.println(mappedMQVal);
  Serial.println("---END LOG---");
  Serial.println();
  delay(500);
};

void alertAir(int ppm){
  if(ppm>=675)
    tone(buzzer,880,500);
  else if(ppm>=600)
    tone(buzzer,440,250);
  noTone(buzzer);
  delay(1000);
}