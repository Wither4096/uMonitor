#pragma once
#include <WiFi.h>
#include "config.h"

class WiFiManager
{
    private:
    const char* ssid_;
    const char* password_;

    public:
    WiFiManager(const char* ssid, const char* password);

    void begin();
    bool isConnected();
};