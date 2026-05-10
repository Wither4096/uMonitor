#pragma once
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "config.h"
#include "SensorReadings.h"

class CloudSync
{
    private:
    const char* firestoreURL_;
    void sendPOSTRequest_(String endpoint, String jsonPayload);
    unsigned long int uploadLastMillis_ = 0;

    public:
    CloudSync(const char* firestoreURL);

    void syncData(SensorReadings &readings, long long int timestamp, unsigned long int currentMillis);
    void sendAlert(const char* type, const char* message, long long int timestamp);
};