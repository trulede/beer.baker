
#ifndef _baker_h
#define _baker_h


#include <stdbool.h>


#define SSID_MAX_LENGTH 32
#define WIFI_PASS_LENGTH 64
#define PLUG_IP_LENGTH 16
#define PLUG_PASS_LENGTH 64


/* config.cpp */
typedef struct {
	bool autoStart;
	struct {
		char ssid[SSID_MAX_LENGTH + 1];
		char password[WIFI_PASS_LENGTH];
	} wifi;
	struct {
		char ip[PLUG_IP_LENGTH];
		long autoOff; // 0 to disable
	} plug;
} baker_config_t;

extern baker_config_t baker_config;


/* command.cpp */
extern void setupCommands(void);
extern void runCommands(void);


/* config.cpp */
extern void loadConfig(void);
extern void saveConfig(void);
extern void printConfig(void);
extern void setConfig(String name, String value);


/* network.cpp */
//extern void startNetwork(config_t* c);


#endif