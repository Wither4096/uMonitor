#include "definitions.h"
#include "SensorManager.h"
#include "SensorReadings.h"
#include "Logging.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


//SensorManager manager(DHT_PIN,DHT21,LM35_PIN,MQ_PIN,LIGHT_RES_PIN);
//SensorReadings readings;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 oled(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire);


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
  //manager.updateReadings(readings);
  SensorManager manager(DHT_PIN,DHT21,LM35_PIN,MQ_PIN,LIGHT_RES_PIN);
  SensorReadings readings = manager.update();

  alertAir(readings.getAirQuality(), readings.getAverageTemperature());

  renderDisplay(readings);

  #ifdef LOGGING
  serialLogDataPoints(readings);
  #endif
}

void alertAir(int airQuality, int temperature){

  if(airQuality <= 45){
    tone(BUZZER_PIN,880);
    digitalWrite(RED_LED_PIN,HIGH);
    analogWrite(GREEN_LED_PIN,0);
    digitalWrite(BLUE_LED_PIN,LOW);

    delay(500);
    noTone(BUZZER_PIN);
    digitalWrite(RED_LED_PIN,LOW);
    analogWrite(GREEN_LED_PIN,0);
    digitalWrite(BLUE_LED_PIN,LOW);
    delay(500);
  }
  
  else if(airQuality <= 59){
    tone(BUZZER_PIN,440);
    digitalWrite(RED_LED_PIN,HIGH);
    analogWrite(GREEN_LED_PIN,32);
    digitalWrite(BLUE_LED_PIN,LOW);

    delay(1000);
    noTone(BUZZER_PIN);
    digitalWrite(RED_LED_PIN,LOW);
    analogWrite(GREEN_LED_PIN,0);
    digitalWrite(BLUE_LED_PIN,LOW);
    delay(1000);
  }

  else {
  //  if(temperature >= 26){ // Warm Condition
  //    digitalWrite(RED_LED_PIN,HIGH);
  //    analogWrite(GREEN_LED_PIN,48);
  //    digitalWrite(BLUE_LED_PIN,LOW);
  //  }
  //  else if(temperature <= 20){ // Cool Condition
  //    digitalWrite(RED_LED_PIN,LOW);
  //    analogWrite(GREEN_LED_PIN,96);
  //    digitalWrite(BLUE_LED_PIN,HIGH);
  //  }
  //  else{ // Nominal Condition
  //    digitalWrite(RED_LED_PIN,LOW);
  //    analogWrite(GREEN_LED_PIN,255);
  //    digitalWrite(BLUE_LED_PIN,LOW);
  //  }
  digitalWrite(RED_LED_PIN,LOW);
  analogWrite(GREEN_LED_PIN,255);
  digitalWrite(BLUE_LED_PIN,LOW);
  }
}

void renderDisplay(SensorReadings& readings){

  unsigned long int displayCurrentMillis = millis();
  if(displayCurrentMillis - displayLastMillis >= DISPLAY_INTERVAL){
    displayLastMillis = displayCurrentMillis;

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