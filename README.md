# tempSensor

## Usage.
```bash
$ tempsensor <settings.ini>
```

## Build.

* mkdir build
* cd build
* cmake ..
* cd ..
* make -C build
* sudo ./build/tn_mesh

## Build gtests.

* mkdir build
* cd build
* cmake .. -Dunittest=ON
* cd ..
* make -C build
* ./build/runUnitTests

## Dependecy

* libcurl4-gnutls-dev
* libsqlite3-dev

## settings.ini
```
# This files contains all settings temperaturesensor,
# edit to fit your needs.
[SensorSettings]
sensor=28-0417a2f482ff
#interval given in minutes
interval=1
[FireBase]
url=https://testing-c408e.firebaseio.com/sensors/testing/current.json
token=AIzaSyDBE1KqXaAvicpGklTBRP0ZvYoBJXG5PoI
[SQLite]
db_file=temperature.db
[mqtt]
server=m24.cloudmqtt.com
port=15786
username=foo
password=bar
topic=lek
```