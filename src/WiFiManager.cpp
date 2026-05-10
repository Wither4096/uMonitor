#include "WiFiManager.h"

WiFiManager::WiFiManager(const char* ssid, const char* password)
:
ssid_(ssid), password_(password)
{};

void WiFiManager::begin()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid_,password_);
    while(WiFi.status() != WL_CONNECTED){
        Serial.println("Connecting...");
        delay(250);
    }

    Serial.println();
    Serial.println("WiFi connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

bool WiFiManager::isConnected(){ return WiFi.status() == WL_CONNECTED; }