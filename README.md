# TempSensor

## Hardware

* Rpi Zero W
* Temperature sensor DS18B20

## Building

### Usage.

```bash
$ tempsensor <settings.ini>
```

### Build.

* mkdir build
* cd build
* cmake ..
* cd ..
* make -C build
* sudo ./build/tempsensor

### Build gtests.

* mkdir build
* cd build
* cmake .. -Dunittest=ON
* cd ..
* make -C build
* ./build/runUnitTests

### Dependecy.

* libsqlite3-dev
* libmosquitto-dev
* libmosquittopp-dev

### settings.ini

```
# This files contains all settings temperaturesensor,
# edit to fit your needs.
[SensorSettings]
sensor=28-0417a2f482ff
#interval given in minutes
interval=1
[SQLite]
db_file=temperature.db
[mqtt]
server=m24.cloudmqtt.com
port=15786
username=foo
password=bar
topic=lek
```

## Frontend

A simple webpage with a basic js mqtt client. Displaying current temperature and the temperature for the last 24h. Edit to fit your needs.

![alt text](./screenshots/screenshot.png)
