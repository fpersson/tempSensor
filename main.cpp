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
#include <functional>
#include "TimerTask.h"
#include "SensorCore.h"
#include "FObserver.h"
#include "CurlFirebase.h"
#include "IniParser.h"

int main(int argc, char **argv){

    std::cout << "Starting..." << std::endl;
    std::string ini_file;

    if(argc != 2){
        std::cout << "Usage: tempsensor <settings.ini>" << std::endl;
        return -1;
    }else{
        ini_file = argv[1];
    }

    std::string sensor;
    std::string url;
    std::string token;

    utils::IniParser iniParser;
    iniParser.parseFile(ini_file);
    TempSensor::TimerTask tt;

    if(iniParser.getValue("sensor").first){
        sensor = iniParser.getValue("sensor").second;
    }else{
        std::cout << "no sensor defined in " << ini_file << std::endl;
    }

    if(iniParser.getValue("url").first){
        url = iniParser.getValue("url").second;
    }else{
        std::cout << "no url defined in " << ini_file << std::endl;
    }

    if(iniParser.getValue("token").first){
        token = iniParser.getValue("token").second;
    }else{
        std::cout << "no token defined in " << ini_file << std::endl;
    }

    TempSensor::SensorCore core(sensor);
    CurlFirebase cf(url, token);

    core.register_observer(cf);

    std::thread t1 = tt.thread_run(std::bind(&TempSensor::SensorCore::readSensor, &core));
    t1.join();

    return 0;
}
