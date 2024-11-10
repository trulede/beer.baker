
#include <Arduino.h>
#include <WiFi.h>
#include "baker.h"


void startNetwork(void) {
	Serial.println("Connecting to WiFi network:");
    Serial.printf("SSID: %s\n", bakerConfig.wifi.ssid);
    Serial.printf("Password: %s\n", bakerConfig.wifi.password);

    WiFi.begin(bakerConfig.wifi.ssid, bakerConfig.wifi.password);
    if (WiFi.status() == WL_CONNECT_FAILED) {
        Serial.println(" failed to connect!");
        return;
    }
    for (int i = 0; i < 60; i++) {
        if (WiFi.status() == WL_CONNECTED) break;
        delay(500);
        Serial.print(".");
    }
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println(" failed to connect!");
        return;
    }
    Serial.println();
    Serial.println("WiFi connected");
    byte mac[6];
    WiFi.macAddress(mac);
    Serial.printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.printf("Address: %s\n", WiFi.localIP().toString().c_str());
}


void stopNetwork(void) {
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Disconnecting from WiFi network");
        WiFi.disconnect();
    }
}
