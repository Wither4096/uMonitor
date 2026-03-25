#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "definitions.h"
#include "SensorReadings.h"

#define WIRE Wire
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 oled(SCREEN_WIDTH,SCREEN_HEIGHT,&WIRE);

DHT dhtSens(dhtPin,DHT11);
SensorReadings vars;

void setup() {
  Serial.begin(9600);
  
  pinMode(mqPin,INPUT);
  pinMode(dhtPin,INPUT);
  pinMode(lightResPin,INPUT);
  pinMode(lm35Pin,INPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(buzzer,OUTPUT);

  dhtSens.begin();

  oled.begin(SSD1306_SWITCHCAPVCC,0x3C);
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.drawBitmap(0,0,BOOTBMP,128,32,WHITE);
  oled.display();

  delay(2500);
  oled.clearDisplay();
}

void loop() {
  vars.setHum(dhtSens.readHumidity());
  vars.setTempDHT(dhtSens.readTemperature());
  vars.setTempLM35((analogRead(lm35Pin)/4095.0)*5.0*10.0);
  vars.setMQVal(analogRead(mqPin));
  vars.setLightVal(analogRead(lightResPin));

  alertAir(map(vars.getGas(),0,4095,0,1023));

  renderDisplay();

  serialLogDataPoints();
}

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

void alertAir(int ppm){
  if(ppm>=600){
    tone(buzzer,880);
    digitalWrite(ledPin,HIGH);
    delay(500);
  }
  
  else if(ppm>=500){
  tone(buzzer,440);
  digitalWrite(ledPin,HIGH);
  delay(1000);
  }

  noTone(buzzer);
  digitalWrite(ledPin,LOW);
}

void renderDisplay(){
  oled.setCursor(0, 0);

  oled.clearDisplay();

  //oled.println("   Live Readings");
  oled.print("    LIT: ");oled.println(vars.getLight()/40.95);
  oled.print("    HUM: ");oled.println(vars.getHum());
  oled.print("    TEMP: ");oled.println(vars.getTempAvg());
  oled.print("    AIR: ");oled.println(map(vars.getGas(),0,4095,0,1023));

  oled.display();
}