#include <DHT.h>

const int analogMQPin=34;
const int dhtPin=33;
const int lm35pin=13;
const int buzzer=15;

DHT dhtSens(dhtPin,DHT11);

float hum=0;
float tempuDHT=0;
float tempuLM35=0;
float mappedLM35Val=0;
float analogMQVal=0;
float mappedMQVal=0;

void setup() {
  pinMode(analogMQPin,INPUT);
  pinMode(dhtPin,INPUT);
  pinMode(lm35pin,INPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  dhtSens.begin();
}

void loop() {
  hum=dhtSens.readHumidity();
  tempuDHT=dhtSens.readTemperature();
  tempuLM35=((analogRead(lm35pin))/4095.0)*100.0;
  analogMQVal=analogRead(analogMQPin);
  mappedMQVal=map(analogMQVal,0,4095,0,1023);
  alertAir(mappedMQVal);
  serialLogDataPoints();
}

void serialLogDataPoints(){
  Serial.println("---START LOG---");
  Serial.print("Humidity: ");Serial.print(hum);Serial.println("%");
  Serial.print("Temperature (DHT11): ");Serial.print(tempuDHT);Serial.println("\xC2\xB0");
  Serial.print("Temperature (LM35): ");Serial.print(tempuLM35);Serial.println("\xC2\xB0");
  Serial.print("Temperature (Average): ");Serial.print((tempuDHT+tempuLM35)/2);Serial.println("\xC2\xB0");
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