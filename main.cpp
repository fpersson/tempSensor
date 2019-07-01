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
