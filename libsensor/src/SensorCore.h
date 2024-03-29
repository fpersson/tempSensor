/*
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
 */


#ifndef TEMPSENSOR_SENSORCORE_H
#define TEMPSENSOR_SENSORCORE_H

#include <string>
#include "FObserver.h"

namespace TempSensor {

    const std::string SYSFS_PATH = "/sys/bus/w1/devices/";
    const std::string SLAVE = "/w1_slave";

    class SensorCore : public  FObserver::Observable{
    public:
        explicit SensorCore(const std::string& sensorPath, const std::string& sensorID);
        void readSensor();

    private:
        std::string file;
    };
} //namespace


#endif //TEMPSENSOR_SENSORCORE_H
