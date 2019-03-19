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

## settings.ini
```
# This files contains all settings temperaturesensor,
# edit to fit your needs.
[SensorSettings]
sensor=28-0417a2f482ff
[FireBase]
url=https://testing-c408e.firebaseio.com/sensors/testing/current.json
token=AIzaSyDBE1KqXaAvicpGklTBRP0ZvYoBJXG5PoI
```