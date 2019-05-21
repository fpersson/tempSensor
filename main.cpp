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
#include "IniParser.h"

#include "DBManager.h"
#include "Mqtt.h"

int main(int argc, char **argv){

    std::cerr << "Starting..." << '\n';
    std::string ini_file;

    if(argc != 2){
        std::cerr << "Usage: tempsensor <settings.ini>\n";
        return -1;
    }else{
        ini_file = argv[1];
    }

    std::string sensor;
    std::string url;
    std::string token;
    std::string db_file;
    long interval=1;

    utils::IniParser iniParser;
    iniParser.parseFile(ini_file);

    if(iniParser.getValue("sensor").first){
        sensor = iniParser.getValue("sensor").second;
    }else{
        std::cerr << "no sensor defined in " << ini_file << '\n';
    }

    if(iniParser.getValue("url").first){
        url = iniParser.getValue("url").second;
    }else{
        std::cerr << "no url defined in " << ini_file << '\n';
    }

    if(iniParser.getValue("token").first){
        token = iniParser.getValue("token").second;
    }else{
        std::cerr << "no token defined in " << ini_file << '\n';
    }

    if(iniParser.getValue("interval").first){
        interval = std::stol(iniParser.getValue("interval").second);
    }else{
        std::cerr << "no interval defined in " << ini_file << " using default 1 minute\n";
    }

    if(iniParser.getValue("db_file").first){
        db_file = iniParser.getValue("db_file").second;
    }else{
        std::cerr << "no db_file defined in " << ini_file << '\n';
    }

    TempSensor::TimerTask tt(interval);

    TempSensor::SensorCore core(sensor);

    DBManager dbManager;
    dbManager.init(db_file);

    TempSensor::MqttSettings mqttSettings;

    mqttSettings.ID=iniParser.getValue("ID").second;
    mqttSettings.server=iniParser.getValue("server").second;
    mqttSettings.port=std::stoi(iniParser.getValue("port").second);//15786;
    mqttSettings.username=iniParser.getValue("username").second;
    mqttSettings.password=iniParser.getValue("password").second;
    mqttSettings.topic=iniParser.getValue("topic").second;

    TempSensor::Mqtt m(mqttSettings);

    core.register_observer(dbManager);
    core.register_observer(m);

    std::thread t1 = tt.thread_run(std::bind(&TempSensor::SensorCore::readSensor, &core));
    t1.join();

    return 0;
}
