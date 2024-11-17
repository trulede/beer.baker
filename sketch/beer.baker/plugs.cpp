
#include <Arduino.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "baker.h"


WiFiClient client;
HTTPClient http;


static DynamicJsonDocument requestPlugS(String method, JsonDocument params) {
    String url = "http://192.168.33.1/rpc";
    String json;
    DynamicJsonDocument doc(256);

    // Build the RPC request.
    doc["id"] = 1;
    doc["method"] = method;
    doc["params"] = params;

    // Post the request.
    Serial.print("Request (POST): ");
    Serial.println(url);
    Serial.println("Body:");
    serializeJsonPretty(doc, Serial);
    Serial.println(); 
    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");
    serializeJson(doc, json);
    Serial.println(); 
    doc.clear();
    int httpCode = http.POST(json);
    if (httpCode > 0) {
        Serial.print("Response (CODE): ");
        Serial.println(httpCode);
        deserializeJson(doc, http.getStream());
        Serial.println("Body:");
        serializeJsonPretty(doc, Serial);   
        Serial.println(); 
    } else {
        Serial.print("Error sending POST request: ");
        Serial.println(httpCode);
    }
    http.end();

    // Return the JSON response.
    return doc;
}


void statusPlugS(void) {
    DynamicJsonDocument doc(64);
    doc["id"] = 0;
    DynamicJsonDocument resp = requestPlugS("Switch.GetStatus", doc);

    if (resp["result"].is<JsonObject>()) {
        // Output state:
        if (resp["result"]["output"].is<bool>()) {
            bakerStatus.plug.switch0.state = resp["result"]["output"];
        } else {
            bakerStatus.plug.switch0.state = false;
            Serial.println("Error: output state not included in result!");
        }
        // Temperature:
        if (resp["result"]["temperature"]["tC"].is<float>()) {
            bakerStatus.plug.switch0.tempC = resp["result"]["temperature"]["tC"];
        }
        // voltage:
        if (resp["result"]["voltage"].is<float>()) {
            bakerStatus.plug.switch0.voltage = resp["result"]["voltage"];
        }
        // current:
        if (resp["result"]["current"].is<float>()) {
            bakerStatus.plug.switch0.current = resp["result"]["current"];
        }
        // apower:
        if (resp["result"]["apower"].is<float>()) {
            bakerStatus.plug.switch0.apower = resp["result"]["apower"];
        }
        // aenergyTotal:
        if (resp["result"]["aenergy"]["total"].is<float>()) {
            bakerStatus.plug.switch0.aenergyTotal = resp["result"]["aenergy"]["total"];
        }
    } else {
        Serial.println("Error: resut set not included in result!");
    }
}


void setPlugS(bool state) {
    DynamicJsonDocument doc(64);
    doc["id"] = 0;
    doc["on"] = state;
    requestPlugS("Switch.Set", doc);
}
