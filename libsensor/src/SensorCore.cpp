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


#include <iostream>
#include <sstream>
#include <iomanip>
#include "IOhelper.h"
#include "SensorCore.h"

namespace TempSensor {
    SensorCore::SensorCore(std::string sensorID) : mSensorID(std::move(sensorID)), file("") {
        file.append(SYSFS_PATH).append(mSensorID).append(SLAVE);
#ifdef DEBUGMODE
        std::cout << "INIT: " << file << std::endl;
#endif

    }

    void SensorCore::readSensor() {
#ifdef DEBUGMODE
        std::cout << "Reading " << file << std::endl;
#endif
        auto fileRead = IO::readFromFile(file);
        if(fileRead.first) {
            IO::StringList sl = IO::split(fileRead.second, '\n');
            IO::StringList sl1 = IO::split(sl[1], ' ');

            std::stringstream ss;
            ss << std::fixed << std::setprecision(2);
            ss << std::stof(IO::split(sl1[9], '=')[1]) / 1000;
#ifdef DEBUGMODE
            std::cout << "FOUND: " <<  ss.str() << std::endl;
#endif
            onEvent(ss.str());
        }else{
            std::cerr << "Could not read sensor: " << file << '\n';
        }
    }

} //namespace