#include "config.h"
#include "SensorManager.h"
#include "SensorReadings.h"
#include "SerialLogging.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire);
unsigned long int displayPrevMillis = 10000;

SensorManager manager(DHT_PIN,DHT21,LM35_PIN,MQ_PIN,LIGHT_RES_PIN);
SensorReadings readings;

unsigned long int alertWarnPrevMillis = 0;
unsigned long int alertCriticalPrevMillis = 0;
bool alertWarnOn = false;
bool alertCriticalOn = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(MQ_PIN,INPUT);
  pinMode(DHT_PIN,INPUT);
  pinMode(LIGHT_RES_PIN,INPUT);
  pinMode(LM35_PIN,INPUT);

  pinMode(RED_LED_PIN,OUTPUT);
  pinMode(GREEN_LED_PIN,OUTPUT);
  pinMode(BLUE_LED_PIN,OUTPUT);

  pinMode(BUZZER_PIN,OUTPUT);

  oled.begin(SSD1306_SWITCHCAPVCC,0x3C);
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(SSD1306_WHITE);
  oled.setTextWrap(false);
  oled.drawBitmap(0,0,BOOTBMP64,SCREEN_WIDTH,SCREEN_HEIGHT,WHITE);
  oled.display();

  delay(2500);

  oled.clearDisplay();
}

void loop() {
  unsigned long int currentMillis = millis();

  manager.updateReadings(readings);
  //SensorManager manager(DHT_PIN,DHT21,LM35_PIN,MQ_PIN,LIGHT_RES_PIN);
  //SensorReadings readings = manager.update();

  handleAlerts(readings.getAirQuality(), currentMillis);

  renderDisplay(readings, currentMillis);

  #ifdef LOGGING
  serialLogDataPoints(readings, currentMillis);
  #endif
}

void handleAlerts(float airQuality, unsigned long int currentMillis){
  if(airQuality <= 45){
    if(!alertCriticalOn){
      if(currentMillis - alertCriticalPrevMillis >= ALERT_CRITICAL_INTERVAL){
        //Reset State
        alertWarnOn = false;
        alertWarnPrevMillis = currentMillis;
        noTone(BUZZER_PIN);
        digitalWrite(RED_LED_PIN, LOW);
        analogWrite(GREEN_LED_PIN, 0);
        digitalWrite(BLUE_LED_PIN, LOW);

        //Set Critical State
        alertCriticalOn = true;
        alertCriticalPrevMillis = currentMillis;

        tone(BUZZER_PIN,880);
        digitalWrite(RED_LED_PIN,HIGH);
        analogWrite(GREEN_LED_PIN,0);
        digitalWrite(BLUE_LED_PIN,LOW);
      }
    }
    else{
      if(currentMillis - alertCriticalPrevMillis >= ALERT_CRITICAL_INTERVAL){
        alertCriticalOn = false;
        alertCriticalPrevMillis = currentMillis;
        
        noTone(BUZZER_PIN);
        digitalWrite(RED_LED_PIN,LOW);
        analogWrite(GREEN_LED_PIN,0);
        digitalWrite(BLUE_LED_PIN,LOW);
      }
    }
  }
  
  else if(airQuality <= 59){    
    if(!alertWarnOn){
      if(currentMillis - alertWarnPrevMillis >= ALERT_WARN_INTERVAL){
        //Reset State
        alertCriticalOn = false;
        alertCriticalPrevMillis = currentMillis;
        noTone(BUZZER_PIN);
        digitalWrite(RED_LED_PIN, LOW);
        analogWrite(GREEN_LED_PIN, 0);
        digitalWrite(BLUE_LED_PIN, LOW);
        
        //Set Warn State
        alertWarnOn = true;
        alertWarnPrevMillis = currentMillis;

        tone(BUZZER_PIN,440);
        digitalWrite(RED_LED_PIN,HIGH);
        analogWrite(GREEN_LED_PIN,32);
        digitalWrite(BLUE_LED_PIN,LOW);
      }
    }

    else{
      if(currentMillis - alertWarnPrevMillis >= ALERT_WARN_INTERVAL){
        alertWarnOn = false;
        alertWarnPrevMillis = currentMillis;

        noTone(BUZZER_PIN);
        digitalWrite(RED_LED_PIN,LOW);
        analogWrite(GREEN_LED_PIN,0);
        digitalWrite(BLUE_LED_PIN,LOW);
      }
    }
  }

  else{
    noTone(BUZZER_PIN);
    digitalWrite(RED_LED_PIN,LOW);
    analogWrite(GREEN_LED_PIN,255);
    digitalWrite(BLUE_LED_PIN,LOW);
  }
}

void renderDisplay(SensorReadings& readings, unsigned long int currentMillis){
  if(currentMillis - displayPrevMillis >= DISPLAY_INTERVAL){
    displayPrevMillis = currentMillis;

    oled.setCursor(0, 0);

    oled.clearDisplay();
    if(readings.getAverageTemperature() == 100.00){ oled.print("TMP: ");oled.println("100.0"); }
    else{ oled.print("TMP: ");oled.println(readings.getAverageTemperature()); }

    if(readings.getHumidity() == 100.00){ oled.print("HUM: ");oled.println("100.0"); }
    else if(isnan(readings.getHumidity())){ oled.print("HUM: ");oled.println("ERROR"); }
    else{ oled.print("HUM: ");oled.println(readings.getHumidity()); }

    if(readings.getAirQuality() == 100.00){ oled.print("AQI: ");oled.println("100.0"); }
    else{ oled.print("AQI: ");oled.println(readings.getAirQuality()); }

    if(readings.getLight() == 100.00){ oled.print("LUX: ");oled.println("100.0"); }
    else{ oled.print("LUX: ");oled.println(readings.getLight()); }

    oled.display();
  }
}