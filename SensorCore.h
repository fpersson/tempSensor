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

#ifndef TEMPSENSOR_SENSORCORE_H
#define TEMPSENSOR_SENSORCORE_H

#include <string>
#include "FObserver.h"

namespace TempSensor {

    /*
#ifdef DEVEL
    const std::string SYSFS_PATH = "./testdata/";
#else
    const std::string SYSFS_PATH = "/sys/bus/w1/devices/";
#endif
     */
    const std::string SYSFS_PATH = "./testdata/";

    const std::string SLAVE = "/w1_slave";

    class SensorCore : public  FObserver::Observable{
    public:
        explicit SensorCore(std::string sensorID);
        void readSensor();

    private:
        std::string mSensorID;
        std::string file;
    };
} //namespace


#endif //TEMPSENSOR_SENSORCORE_H
