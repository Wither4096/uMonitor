#pragma once
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "config.h"
#include "SensorReadings.h"

class CloudSync
{
    private:
    const char* firestoreURL_;
    void sendPOSTRequest(String endpoint, String jsonPayload);
    unsigned long int uploadLastMillis_ = 0;
    public:
    CloudSync(const char* firestoreURL);
    void syncData(SensorReadings &readings);
    void sendAlert(const char* type, const char* message);
};