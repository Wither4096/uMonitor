#include "CloudSync.h"

CloudSync::CloudSync(const char* firestoreURL)
:
firestoreURL_(firestoreURL)
{}

void CloudSync::syncData(SensorReadings& readings, unsigned long int currentMillis)
{
    if(currentMillis - uploadLastMillis_ >= UPLOAD_INTERVAL){
        uploadLastMillis_ = currentMillis;
        StaticJsonDocument<512> doc;

        doc["temperature"] = readings.getAverageTemperature();
        doc["humidity"] = readings.getHumidity();
        doc["aqi"] = readings.getAirQuality();
        doc["light"] = readings.getLight();

        String payload;
        serializeJson(doc, payload);

        sendPOSTRequest("/telemetry", payload);
    }
}

void CloudSync::sendPOSTRequest(String endpoint, String jsonPayload) {
    HTTPClient http;

    String fullURL = String(firestoreURL_) + endpoint;

    http.begin(fullURL);
    http.addHeader("Content-Type", "application/json");

    int responseCode = http.POST(jsonPayload);
    Serial.print("HTTP Response Code: ");
    Serial.println(responseCode);

    if (responseCode > 0){
        String response = http.getString();
        Serial.println(response);
    }

    else{ Serial.println("HTTP Request Failed"); }

    http.end();
}

void CloudSync::sendAlert(const char* type, const char* message) {
    StaticJsonDocument<256> doc;
    doc["type"] = type;
    doc["message"] = message;
    String payload;
    serializeJson(doc, payload);
    sendPOSTRequest("/alerts", payload);
}

