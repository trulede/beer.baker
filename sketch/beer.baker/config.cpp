
#include <Arduino.h>
#include <Preferences.h>
#include "baker.h"


#define BEER_BAKER_NS "beer.baker"
#define BAKER_CONFIG "baker_config"


baker_config_t baker_config;
Preferences prefs;


void loadConfig(void) {
	if (!prefs.begin(BEER_BAKER_NS, true)) {
		Serial.println("unable to open config, could not begin NS");
		return;
	}
	prefs.getBytes(BAKER_CONFIG, &baker_config, sizeof(baker_config_t));
	prefs.end();
}


void saveConfig(void) {
	Serial.print("saving config ...");
	if (!prefs.begin(BEER_BAKER_NS, false)) {
		Serial.println("unable to save config, could not begin NS");
		return;
	}
	size_t len = prefs.putBytes(BAKER_CONFIG, &baker_config, sizeof(baker_config_t));
	Serial.printf(" %d bytes written\n", len);
	prefs.end();
}


void printConfig(void) {
	Serial.println("");
	Serial.println("Config");
	Serial.println("------");
	Serial.printf("auto-start = %d\n", baker_config.autoStart);
	Serial.printf("wifi-ssid = %s\n", baker_config.wifi.ssid);
	Serial.printf("wifi-pass = %s\n", baker_config.wifi.password);
	Serial.printf("plug-ip = %s\n", baker_config.plug.ip);
	Serial.printf("plug-auto-off = %d\n", baker_config.plug.autoOff);
}


void setConfig(String name, String value) {
  	Serial.printf("set config: %s = %s\n", name, value);
	if (name == "auto-start") {
		if (value == "true" || value == "1") {
			baker_config.autoStart = true;
		} else if (value == "false" || value == "0") {
			baker_config.autoStart = false;
		}
	} else if (name == "wifi-ssid") {
		snprintf(baker_config.wifi.ssid, sizeof(baker_config.wifi.ssid), "%s", value);
	} else if (name == "wifi-pass") {
		snprintf(baker_config.wifi.password, sizeof(baker_config.wifi.password), "%s", value);
	} else if (name == "plug-ip") {
		snprintf(baker_config.plug.ip, sizeof(baker_config.plug.ip), "%s", value);
	} else if (name == "plug-auto-off") {
		long v = value.toInt();
		if (v >= 0) baker_config.plug.autoOff = v;
	}
}
