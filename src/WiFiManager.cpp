#include "WiFiManager.h"

WiFiManager::WiFiManager(const char* ssid, const char* password)
:
ssid_(ssid), password_(password)
{};

void WiFiManager::begin()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid_,password_);
    for(int i = 0; i < 150; i++){
        if(WiFi.status() != WL_CONNECTED){
            Serial.println("Connecting...");
            delay(50);
        }
    }
    Serial.println();
    if(!isConnected()){ Serial.println("Connection Timeout!"); }
    else{
        Serial.println("WiFi connected");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    }
}

bool WiFiManager::isConnected(){ return WiFi.status() == WL_CONNECTED; }

