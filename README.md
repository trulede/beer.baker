# Beer Baker

Beer brewing temperature control.


## BOM

* [Waveshare ESP32-S3-LCD-1.28](https://www.waveshare.com/wiki/ESP32-S3-LCD-1.28)
* [Shelly Plug S](https://www.shelly.com/products/shelly-plug-s-gen3)
* DS18B20 temperature sensor
* 4.7k resistor (between VCC and Data connectors of DS18B20)
* Terrarium heat mat
* Powerbank (for the ESP32, optional, otherwise simple USB)


## Operation

### CLI

```sh
# Setup the config with a temperature sample bias:
$ config-set -name "ds-offset" -value "-2"
$ config-save
16:24:16.877 -> saving config ... 124 bytes written
$ restart

# Print the config, then sample temperature:
$ config
Config
------
auto-start = 0
wifi-ssid = ShellyPlusPlugS-D4D4DAED3310
wifi-pass = BeerHeater
plug-ip = 
plug-auto-off = 0
ds-offset = -2.000000
$ sample
Scan OW Bus:
  Device count: 1
  DS18 count: 1
Request temperatures ... OK.
 
Sample
------
ds18b20:
  temperature C = 20.375000 (sensor value: 22.375000)

$ sample
Sample
------
ds18b20:
  temperature C = 20.312500 (sensor value: 22.312500)

# Plug ON
$ on

# Plug OFF
$ off
```

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

```text
Vcc (red) o----------o------o H1 Pin 18 (VCC)
                    .|_
                    |  |
                    |  | 4.7k
                    |__|
                     |
Data (yellow) o------o------o H1 Pin 19 (GP 14)
Gnd (black) o---------------o H1 Pin 20 (GND)
```


## Design

### Feature Set

1. CLI (USB Serial) for configuration.
2. Persist configuration between restarts.
3. Programable temperature sequence.
4. Predictive control algorithm.
5. Low power mode (off between samples).
6. Over-temperature protection; regular control of PlugS, Auto Off configuration.
7. Connection to Tilt 2 SG monitor (bluetooth).
8. Visualization via screen/dial (on/off/temp/target), touch to wake.
9. Touch screen interactions (on/off/stop)
10. Notification and alerts (Bluesky via WiFi/Bluetooth gateway).


## Links and References

* [ESP32-S3-LCD-1.28](https://www.waveshare.com/wiki/ESP32-S3-LCD-1.2)
  * [Onboard Interface](https://www.waveshare.com/wiki/ESP32-S3-LCD-1.28#Onboard_Interface)
  * [ESP32-S3 Datasheet](https://www.espressif.com.cn/sites/default/files/documentation/esp32-s3_datasheet_en.pdf)
* Arduino Libraries:
  * [Dallas Temperature Control Library](https://www.milesburton.com/w/index.php/Dallas_Temperature_Control_Library)
  * [Arduino Json](https://arduinojson.org/)
  * [WiFi Client](https://reference.arduino.cc/reference/en/libraries/wifi/wificlient/)
  * [HTTP Client](https://docs.arduino.cc/libraries/httpclient/)
  * [Simple CLI](https://github.com/SpacehuhnTech/SimpleCLI)