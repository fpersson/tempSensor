/*
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA  02110-1301, USA.

    ---
    Copyright (C) 2019, Fredrik Persson <fpersson.se@gmail.com>
 */

#include <iostream>
#include "IOhelper.h"
#include "SensorCore.h"

namespace TempSensor {
    SensorCore::SensorCore(std::string sensorID) : mSensorID(std::move(sensorID)), file("") {
        file.append(SYSFS_PATH).append(mSensorID).append(SLAVE);
        std::cout << "INIT: " << file << std::endl;

    }

    void SensorCore::readSensor() {
        std::cout << "Reading " << file << std::endl;
        std::string data = IO::readFromFile(file);
        IO::StringList sl = IO::split(data, '\n');
        IO::StringList sl1 = IO::split(sl[1], ' ');
        std::string tmp = std::to_string(std::stof(IO::split(sl1[9], '=')[1])/1000);
        std::cout << "FOUND: " <<  tmp << std::endl;
        onEvent(tmp);
    }

} //namespace