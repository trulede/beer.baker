# Beer Baker

Beer brewing temperature control.


## BOM

* [Waveshare ESP32-S3-LCD-1.28](https://www.waveshare.com/wiki/ESP32-S3-LCD-1.28)
* [Shelly Plug S](https://www.shelly.com/products/shelly-plug-s-gen3)
* DS18B20 temperature sensor
* Terrarium heat mat.
* Powerbank (for the ESP32, optional, otherwise simple USB)


## Hardware Notes

### Waveshare ESP32-S3-LCD

#### Configure Arduino IDE/Project

Board: ESP32S3 Dev Module
Port: USB 6 (or similar)


### Shelly Plug S

#### Configuration

Adjust settings from default:

| Setting               | Value        |
| :-------------------- |:-------------|
| WiFi Mode             | Access Point (AP) Mode |
| WiFi Network SSID     | (SSID is predefined and cannot be configured) |
| WiFi Network Password | BeerHeater (or your choice) |
| IP Address            | 192.168.33.1 (default, change if required) |
| Timer / Auto Off      | Enable, starting value 1800 (*) |

> (*) The Auto Off timer will protect the beer from overheating in the case that
the temperature controller fails. Adjust according to your individual setup. 

Factory reset: Plug/power device and then hold control button for 10 seconds (and within 1 minute of powering the device).


### DS18B20

1-Wire Interface:

Red VCC (3 - 5.5V)
Yellow Data
Black Ground


## Design



## Features

Key:

D: design decision
Q: open question


### Network Services

D: TCP Client.

D: WiFi Driver.

Q: BT connection to fermentation sensor (temperature/gravity)?


### Display

D: Heater On/Off (i.e. the last Shelly Plug S command).

D: Temperature (actual/target).

Q: Trend graph?

Q: Gravity (start value, trend)?

D: WiFi Status

Q: Shelly Plug S status (i.e. result of last command)?


### Operation

Q: Temperature sample rate and target temperature algorithm? Self adjusting?

Q: Retry for failed commands, interval?

Q: Method for adjusting the target temperature? Via GUI with Widget?

Q: Start button, cause initial values to be persisted (i.e. gravity)? Some kind of session storage; for reset/restart/power events?

