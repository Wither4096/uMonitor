#include "definitions.h"
#include "SensorManager.h"
#include "SensorReadings.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


//SensorManager manager(DHT_PIN,11,LM35_PIN,MQ_PIN,LIGHT_RES_PIN);
//SensorReadings readings;

constexpr int SCREEN_WIDTH = 128;
constexpr int SCREEN_HEIGHT = 64;
Adafruit_SSD1306 oled(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire);


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
  oled.setTextSize(2);
  oled.setTextColor(SSD1306_WHITE);
  oled.drawBitmap(0,0,BOOTBMP64,SCREEN_WIDTH,SCREEN_HEIGHT,WHITE);
  oled.display();

  delay(2500);
  oled.clearDisplay();
}

void loop() {
  //manager.updateReadings(readings);
  SensorManager manager(DHT_PIN,DHT21,LM35_PIN,MQ_PIN,LIGHT_RES_PIN);
  SensorReadings readings = manager.update();

  alertAir(readings.getAirQuality());

  renderDisplay(readings);

  #ifdef LOGGING
  serialLogDataPoints(readings);
  #endif
}

void alertAir(int airQuality){
  if(airQuality >= 60){
    tone(BUZZER_PIN,880);
    digitalWrite(LED_PIN,HIGH);
    delay(500);
  }
  
  else if(airQuality >= 50){
  tone(BUZZER_PIN,440);
  digitalWrite(LED_PIN,HIGH);
  delay(1000);
  }

  noTone(BUZZER_PIN);
  digitalWrite(LED_PIN,LOW);
  delay(500);
}

void renderDisplay(SensorReadings& readings){

  unsigned long int displayCurrentMillis=millis();
  if(displayCurrentMillis - displayLastMillis >= DISPLAY_INTERVAL){
    displayLastMillis = displayCurrentMillis;

    oled.setCursor(0, 0);

    oled.clearDisplay();
    oled.print("TMP: ");oled.println(readings.getAverageTemperature());
    oled.print("HUM: ");oled.println(readings.getHumidity());
    oled.print("AQI: ");oled.println(readings.getAirQuality());
    oled.print("LUX: ");oled.println(readings.getLight());

    oled.display();
  }
}