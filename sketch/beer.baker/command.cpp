
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


void statusCommand(cmd* c) {
    Command cmd(c);

    Serial.println("");
	Serial.println("Status");
	Serial.println("------");
    startNetwork();
    stopNetwork();
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

    cmdConfigPrint = cli.addCommand("config-print", configPrintCommand);
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
