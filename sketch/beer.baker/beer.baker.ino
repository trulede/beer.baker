
#include "baker.h"


BakerConfig_t bakerConfig;
BakerStatus_t bakerStatus;


void setup() {
    Serial.begin(115200);
    delay(2000);
    Serial.println("Beer Baker: setup ...");

    /* Setup the CLI. */
    setupCommands();

    /* Load config, if available. */
    loadConfig();
    printConfig();

    /* Initialise board features. */

    /* Start network. */
    //startNetwork(&config);
}

void loop() {
    runCommands();
    // Sample/adjust/update GUI

 	  // Wait, touch or command
 	  //   but only restart timer on config change
}
