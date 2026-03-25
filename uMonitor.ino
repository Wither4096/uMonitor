#include "definitions.h"
#include "SensorManager.h"
#include "SensorReadings.h"

#define LOGGING 1

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


SensorManager manager(DHT_PIN,11,LM35_PIN,MQ_PIN,LIGHT_RES_PIN);
SensorReadings readings;

#define WIRE Wire
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 oled(SCREEN_WIDTH,SCREEN_HEIGHT,&WIRE);


void setup() {
  Serial.begin(9600);
  
  pinMode(MQ_PIN,INPUT);
  pinMode(DHT_PIN,INPUT);
  pinMode(LIGHT_RES_PIN,INPUT);
  pinMode(LM35_PIN,INPUT);
  pinMode(LED_PIN,OUTPUT);
  pinMode(BUZZER_PIN,OUTPUT);


  oled.begin(SSD1306_SWITCHCAPVCC,0x3C);
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.drawBitmap(0,0,BOOTBMP,128,32,WHITE);
  oled.display();

  delay(2500);
  oled.clearDisplay();

  //manager.init();
}

void loop() {
  //readings.updateValues(
  //float(dhtSens.readHumidity()),
  //float(dhtSens.readTemperature()),
  //float(((analogRead(LM35_PIN)/4095.0)*5.0*10.0)),
  //float(analogRead(MQ_PIN)),
  //float(analogRead(LIGHT_RES_PIN))
  //);
  
  manager.updateReadings(readings);

  alertAir(readings.getAirQuality());

  renderDisplay(readings);

  #ifdef LOGGING
  serialLogDataPoints();
  #endif
}

void alertAir(int gas){
  if(gas>=60){
    tone(BUZZER_PIN,880);
    digitalWrite(LED_PIN,HIGH);
    delay(500);
  }
  
  else if(gas>=50){
  tone(BUZZER_PIN,440);
  digitalWrite(LED_PIN,HIGH);
  delay(1000);
  }

  noTone(BUZZER_PIN);
  digitalWrite(LED_PIN,LOW);
}

void renderDisplay(SensorReadings& readings){
  oled.setCursor(0, 0);

  oled.clearDisplay();

  //oled.println("   Live Readings");
  oled.print("    TMP: ");oled.println(readings.getAverageTemperature());
  oled.print("    HUM: ");oled.println(readings.getHumidity());
  oled.print("    AQI: ");oled.println(readings.getAirQuality());
  oled.print("    LUX: ");oled.println(readings.getLight());

  oled.display();
}