
#include <OneWire.h>
#include <DallasTemperature.h>
#include "baker.h"


#define ONE_WIRE_BUS 4
#define ONE_WIRE_VCC 4
#define ONE_WIRE_GND 4


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


void readSensorTemperature(void) {
    sensors.begin();
    bakerStatus.ds.tempC = sensors.getTempCByIndex(0);
}
