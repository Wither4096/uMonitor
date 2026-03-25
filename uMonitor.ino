#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "definitions.h"
#include "SensorReadings.h"

#define LOGGING 1

#define WIRE Wire
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 oled(SCREEN_WIDTH,SCREEN_HEIGHT,&WIRE);

DHT dhtSens(DHT_PIN,DHT11);
SensorReadings readings;

void setup() {
  Serial.begin(9600);
  
  pinMode(MQ_PIN,INPUT);
  pinMode(DHT_PIN,INPUT);
  pinMode(LIGHT_RES_PIN,INPUT);
  pinMode(LM35_PIN,INPUT);
  pinMode(LED_PIN,OUTPUT);
  pinMode(BUZZER_PIN,OUTPUT);

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
  //readings.setHum(dhtSens.readHumidity());
  //readings.setTempDHT(dhtSens.readTemperature());
  //readings.setTempLM35((analogRead(LM35_PIN)/4095.0)*5.0*10.0);
  //readings.setgas(analogRead(MQ_PIN));
  //readings.setLightVal(analogRead(LIGHT_RES_PIN));
  readings.updateValues( float(dhtSens.readHumidity()) , float(dhtSens.readTemperature()) , float(((analogRead(LM35_PIN)/4095.0)*5.0*10.0)) , float(analogRead(MQ_PIN)) , float(analogRead(LIGHT_RES_PIN)) );

  alertAir(map(readings.getGas(),0,4095,0,1023));

  renderDisplay();

  #ifdef LOGGING
  serialLogDataPoints();
  #endif
}

void alertAir(int gas){
  if(gas>=600){
    tone(BUZZER_PIN,880);
    digitalWrite(LED_PIN,HIGH);
    delay(500);
  }
  
  else if(gas>=500){
  tone(BUZZER_PIN,440);
  digitalWrite(LED_PIN,HIGH);
  delay(1000);
  }

  noTone(BUZZER_PIN);
  digitalWrite(LED_PIN,LOW);
}

void renderDisplay(){
  oled.setCursor(0, 0);

  oled.clearDisplay();

  //oled.println("   Live Readings");
  oled.print("    LIT: ");oled.println(readings.getLight()/40.95);
  oled.print("    HUM: ");oled.println(readings.getHum());
  oled.print("    TEMP: ");oled.println(readings.getTempAvg());
  oled.print("    AIR: ");oled.println(map(readings.getGas(),0,4095,0,1023));

  oled.display();
}