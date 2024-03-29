# TempSensor

## Hardware Requirement

* Rpi [Zero W](https://www.electrokit.com/produkt/raspberry-pi-zero-w-board/)
* Temperature sensor [DS18B20](https://www.kjell.com/se/produkter/el-verktyg/utvecklingskit/arduino/tillbehor/temperatursensor-med-kabel-for-arduino-p87081)

## Building

### Usage.

```bash
$ tempsensor <settings.ini>
```

### Build.
```bash
$ mkdir build
$ cd build
$ cmake ..
$ cd ..
$ make -C build
$ sudo ./build/tempsensor
```

### Install
```bash
$ sudo make install -C build
```
This will install
* tempsensor at /usr/local/bin/tempsensor
* settings.ini at /etc/tempsensor/settings.ini

### Build gtests.
```bash
$ mkdir build
$ cd build
$ cmake .. -Dunittest=ON
$ cd ..
$ make -C build
$ ./build/runUnitTests
```
### Build doc.
This step require doxygen and sphinx
```bash
$ mkdir build
$ cd build
$ cmake .. -Ddoc=ON
$ cd ..
$ make doc -C build
```

### Dependecy.

#### Ubuntu/Raspberry OS (Lite)
* libsqlite3-dev
* libmosquitto-dev
* libmosquittopp-dev

#### OpenSuse TW
```bash
$ sudo zypper install sqlite3-devel libmosquitto1 libmosquittopp1 mosquitto-devel
```

### Install prebuild package from OBS on rpi with OpenSUSE
```bash
$ sudo zypper addrepo https://download.opensuse.org/repositories/home:/fpersson/openSUSE_Factory_ARM/home:fpersson.repo
$ sudo zypper install tempSensor
```

### settings.ini

```
# This files contains all settings temperaturesensor,
# edit to fit your needs.
[SensorSettings]
sensor=28-0417a2f482ff
base_path=./testdata #optional
[SQLite]
db_file=./testdata/temperature.db
[Mqtt]
ID=foo1
server=m24.cloudmqtt.com
port=15786
username=test
password=test

[Topic1]
topic=playground
#interval given in minutes
interval=1

[Topic2]
topic=playground_history
#interval given in minutes
interval=1
```

## Frontend

A simple webpage with a basic js mqtt client. Displaying current temperature and the temperature for the last 24h. Edit to fit your needs.

![alt text](./screenshots/screenshot.png)

## Hardware

### Setup DS18B20
Your DS18B20 should be connected to pin 7 (BCM4), gnd, and 3v.

Edit /boot/config.txt
```bash
# Enable gpio for DS18BS20
dtoverlay=w1-gpio,pinout=4,pullup=on
```

Edit /etc/modules
```bash
# /etc/modules: kernel modules to load at boot time.
#
# This file contains the names of kernel modules that should be loaded
# at boot time, one per line. Lines beginning with "#" are ignored.
w1-gpio pullup=1
w1-therm strong_pullup=1
```

check for /sys/bus/w1/devices/28-xxxxxxxxxx

### Autostart with systemd
To autostart the sensor at boot (or restart if it crash) use systemd.

```bash
$ mkdir ~/bin
$ cp <src_path>/build/tempsensor ~/bin/
$ sudo cp <src_path>/systemd/tempsensor.service /etc/systemd/system/tempsensor.service
$ sudo systemctl enable tempsensor.service
$ sudo systemctl start tempsensor.service
```

## Setup Sphinx for documentation
```bash
$ sudo pip install sphinx
$ sudo pip install sphinx_rtd_theme
$ sudo pip install breathe
```


## Licens (Zero Clause BSD)
```
    Copyright (C) 2019, Fredrik Persson <fpersson.se@gmail.com>

    Permission to use, copy, modify, and/or distribute this software
    for any purpose with or without fee is hereby granted.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
    AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
    INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
    OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
    OF THIS SOFTWARE.
```
