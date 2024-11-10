
#include <Arduino.h>
#include <Preferences.h>
#include "baker.h"


#define BEER_BAKER_NS "beer.baker"
#define BAKER_CONFIG "bakerConfig"


BakerConfig_t bakerConfig;
Preferences prefs;


void loadConfig(void) {
	if (!prefs.begin(BEER_BAKER_NS, true)) {
		Serial.println("unable to open config, could not begin NS");
		return;
	}
	prefs.getBytes(BAKER_CONFIG, &bakerConfig, sizeof(BakerConfig_t));
	prefs.end();
}


void saveConfig(void) {
	Serial.print("saving config ...");
	if (!prefs.begin(BEER_BAKER_NS, false)) {
		Serial.println("unable to save config, could not begin NS");
		return;
	}
	size_t len = prefs.putBytes(BAKER_CONFIG, &bakerConfig, sizeof(BakerConfig_t));
	Serial.printf(" %d bytes written\n", len);
	prefs.end();
}


void printConfig(void) {
	Serial.println("");
	Serial.println("Config");
	Serial.println("------");
	Serial.printf("auto-start = %d\n", bakerConfig.autoStart);
	Serial.printf("wifi-ssid = %s\n", bakerConfig.wifi.ssid);
	Serial.printf("wifi-pass = %s\n", bakerConfig.wifi.password);
	Serial.printf("plug-ip = %s\n", bakerConfig.plug.ip);
	Serial.printf("plug-auto-off = %d\n", bakerConfig.plug.autoOff);
}


void setConfig(String name, String value) {
  	Serial.printf("set config: %s = %s\n", name.c_str(), value.c_str());
	if (name == "auto-start") {
		if (value == "true" || value == "1") {
			bakerConfig.autoStart = true;
		} else if (value == "false" || value == "0") {
			bakerConfig.autoStart = false;
		}
	} else if (name == "wifi-ssid") {
		snprintf(bakerConfig.wifi.ssid, sizeof(bakerConfig.wifi.ssid), "%s", value.c_str());
	} else if (name == "wifi-pass") {
		snprintf(bakerConfig.wifi.password, sizeof(bakerConfig.wifi.password), "%s", value.c_str());
	} else if (name == "plug-ip") {
		snprintf(bakerConfig.plug.ip, sizeof(bakerConfig.plug.ip), "%s", value.c_str());
	} else if (name == "plug-auto-off") {
		long v = value.toInt();
		if (v >= 0) bakerConfig.plug.autoOff = v;
	}
}
