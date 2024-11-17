
#include <Arduino.h>
#include <SimpleCLI.h>
#include "baker.h"


/* CLI Instance. */
SimpleCLI cli;


/* Command Variables. */
Command cmdHelp;
Command cmdConfigPrint;
Command cmdConfigSet;
Command cmdConfigSave;
Command cmdStart;
Command cmdStop;
Command cmdStatus;
Command cmdPlugOn;
Command cmdPlugOff;
Command cmdSample;
Command cmdRestart;


void helpCommand(cmd* c) {
    Command cmd(c);
    Serial.println("Beer Baker: brew temperature regulation");
    Serial.println("");
    Serial.println("Commands:");
    Serial.println(cli.toString());
}


void configPrintCommand(cmd* c) {
    Command cmd(c);
	printConfig();
}


void configSetCommand(cmd* c) {
    Command cmd(c);
    bool networkChanged = false;

	setConfig(cmd.getArgument("name").getValue(), cmd.getArgument("value").getValue());
	printConfig();
}


void configSaveCommand(cmd* c) {
    Command cmd(c);
	saveConfig();
}


void restartCommand(cmd* c) {
    Command cmd(c);
    Serial.println("restarting controller ...");
	ESP.restart();
}


static void printStatus(void) {
    Serial.println("");
	Serial.println("Status");
	Serial.println("------");
    Serial.println("plug:");
    Serial.printf("  switch state  = %d\n", bakerStatus.plug.switch0.state);
    Serial.printf("  apower        = %f\n", bakerStatus.plug.switch0.apower);
    Serial.printf("  voltage       = %f\n", bakerStatus.plug.switch0.voltage);
    Serial.printf("  current       = %f\n", bakerStatus.plug.switch0.current);
    Serial.printf("  total energy  = %f\n", bakerStatus.plug.switch0.aenergyTotal);
    Serial.printf("  temperature C = %f\n", bakerStatus.plug.switch0.tempC);
    Serial.println("ds18b20:");
    Serial.printf("  temperature C = %f\n", bakerStatus.ds.tempC);
}


static void printSample(void) {
    Serial.println("");
	Serial.println("Sample");
	Serial.println("------");
    Serial.println("ds18b20:");
    Serial.printf("  temperature C = %f (sensor value: %f)\n", (bakerStatus.ds.tempC + bakerConfig.ds.offsetC), bakerStatus.ds.tempC);
}


void statusCommand(cmd* c) {
    Command cmd(c);

    // Refresh the status.
    startNetwork();
    statusPlugS();
    readSensorTemperature();
    stopNetwork();
    printStatus();
}


void plugOnCommand(cmd* c) {
    Command cmd(c);

    startNetwork();
    setPlugS(true);
    statusPlugS();
    stopNetwork();
    printStatus();
}


void plugOffCommand(cmd* c) {
    Command cmd(c);

    startNetwork();
    setPlugS(false);
    statusPlugS();
    stopNetwork();
    printStatus();
}


void sampleCommand(cmd* c) {
    Command cmd(c);
    
    readSensorTemperature();
    printSample();
}


void nopCommand(cmd* c) {
    Command cmd(c);
    Serial.println("Not implemented: " + cmd.getName());
}


void errorCallback(cmd_error* e) {
    CommandError cmdError(e);

    Serial.print("ERROR: ");
    Serial.println(cmdError.toString());
    Serial.println(cli.toString());

    if (cmdError.hasCommand()) {
        Serial.print("Did you mean \"");
        Serial.print(cmdError.getCommand().toString());
        Serial.println("\"?");
    }
}


void setupCommands(void) {
    cmdHelp = cli.addCommand("help", helpCommand);
    cmdHelp.setDescription("print help");

    cmdConfigPrint = cli.addCommand("config", configPrintCommand);
    cmdConfigPrint.setDescription("print configuration");

    cmdConfigSet = cli.addCommand("config-set", configSetCommand);
    cmdConfigSet.addPositionalArgument("name");
    cmdConfigSet.addPositionalArgument("value");
    cmdConfigSet.setDescription("set configuration value");

	cmdConfigSave = cli.addCommand("config-save", configSaveCommand);
    cmdConfigSave.setDescription("save configuration");


    cmdStart = cli.addCommand("start", nopCommand);
    cmdStop = cli.addCommand("stop", nopCommand);
    cmdStatus = cli.addCommand("status", statusCommand);

    cmdPlugOn = cli.addCommand("on", plugOnCommand);
    cmdPlugOff = cli.addCommand("off", plugOffCommand);

    cmdSample = cli.addCommand("sample", sampleCommand);

	cmdHelp = cli.addCommand("restart", restartCommand);
    cmdHelp.setDescription("restart the controller");

    cli.setOnError(errorCallback);
}


void runCommands(void) {
    while (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        Serial.print("# ");
        Serial.println(input);
        cli.parse(input);
    }
}
