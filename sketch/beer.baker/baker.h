
#ifndef _baker_h
#define _baker_h


#include <stdbool.h>
#include <stdint.h>


#define SSID_MAX_LENGTH 32
#define WIFI_PASS_LENGTH 64
#define PLUG_IP_LENGTH 16
#define PLUG_PASS_LENGTH 64


typedef struct {
	bool autoStart;
	struct {
		char ssid[SSID_MAX_LENGTH + 1];
		char password[WIFI_PASS_LENGTH];
	} wifi;
	struct {
		char ip[PLUG_IP_LENGTH];
		uint32_t autoOff; // 0 to disable
	} plug;
} BakerConfig_t;

extern BakerConfig_t bakerConfig;


typedef struct {
    struct {
        bool switchState;
    } plug;
    struct {
        uint32_t tempKelvin;
        int32_t tempC;
    } ds;
} BakerStatus_t;

//extern BakerStatus_t bakerStatus;


/* command.cpp */
extern void setupCommands(void);
extern void runCommands(void);

/* config.cpp */
extern void loadConfig(void);
extern void saveConfig(void);
extern void printConfig(void);
extern void setConfig(String name, String value);

/* network.cpp */
extern void startNetwork(void);
extern void stopNetwork(void);

#endif