
#include <OneWire.h>
#include <DallasTemperature.h>
#include "baker.h"

// ESP32-S3-LCD onboard interface (https://www.waveshare.com/wiki/ESP32-S3-LCD-1.28#Onboard_Interface.)
//   Orientation: USB connector above.
//     H1 (left); pin 1 top left, pin 2 top right, pin 19 bottom left, pin 20 bottom right.
//     H2 (right); pin 20 top left, pin 19 top right, pin 2 bottom left, pin 1 bottom right.
//
// VCC (red) o----------o------o H1 Pin 18 (VCC)
//                     .|_
//                     |  |
//                     |  | 4.7k
//                     |__|
//                      |
// Data (yellow) o------o------o H1 Pin 19 (GP 14)
// Gnd (black) o---------------o H1 Pin 20 (GND)

#define ONE_WIRE_BUS 14  // (yellow) GP 14 => H1 Pin 19
#define ONE_WIRE_VCC -1  // (red) H1 Pin 18
#define ONE_WIRE_GND -1  // (black) H1 Pin 20


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
bool setupOW = false;

void setupSensor(void) {
    if (setupOW) return;

    Serial.println("Scan OW Bus:");
    sensors.begin();
    int owDeviceCount = sensors.getDeviceCount();
    int owDs18Count = sensors.getDS18Count();
    Serial.printf("  Device count: %d\n", owDeviceCount);
    Serial.printf("  DS18 count: %d\n", owDs18Count);

    setupOW = true;
}


void readSensorTemperature(void) {
    setupSensor();
    Serial.print("Request temperatures ...");
    sensors.requestTemperatures();
    Serial.println(" OK.");
    float tempC = sensors.getTempCByIndex(0);
    if (tempC == DEVICE_DISCONNECTED_C) {
        Serial.printf("Error: could not read temperature from DS18B20 on bus %d\n", ONE_WIRE_BUS);
    } else {
        bakerStatus.ds.tempC = tempC;
    }
}
