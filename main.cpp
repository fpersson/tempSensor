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

#include "libutils/src/TimerTask.h"
#include "libsensor/src/SensorCore.h"
#include "FObserver.h"
#include "IniParser.h"

#include "libsensor/src/DBManager.h"
#include "Mqtt.h"
#include "History.h"
#include "HistoryData.h"
#include "libsensor/src/MqttClient.h"
#include "Keys.h"

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

    std::string history_topic = "N/A";

    utils::IniParser iniParser;
    iniParser.parseFile(ini_file);

    if(iniParser.getValue(core::key::SENSOR).first){
        sensor = iniParser.getValue(core::key::SENSOR).second;
    }else{
        std::cerr << "no sensor defined in " << ini_file << '\n';
    }

    if(iniParser.getValue(core::key::TOPIC1_INTERVAL).first){
        interval = std::stol(iniParser.getValue(core::key::TOPIC1_INTERVAL).second);
    }else{
        std::cerr << "no interval defined in " << ini_file << " using default 1 minute\n";
    }

    if(iniParser.getValue(core::key::SQLITE_DB).first){
        db_file = iniParser.getValue(core::key::SQLITE_DB).second;
    }else{
        std::cerr << "no db_file defined in " << ini_file << '\n';
    }

    if(iniParser.getValue(core::key::TOPIC2_TOPIC).first){
        history_topic = iniParser.getValue(core::key::TOPIC2_TOPIC).second;
    }else{
        std::cerr << "no Topic2.topic defined in " << ini_file << '\n';
    }

    TempSensor::TimerTask readSensorTask(interval);
    TempSensor::TimerTask postHistoryTask(interval); //@todo, set its own interval

    std::string sensor_path;
    auto [isPathConfigured, path] = iniParser.getValue(core::key::SENSOR_BASEPATH);

    if(isPathConfigured){
        sensor_path = path;
    }else{
        sensor_path = TempSensor::SYSFS_PATH;
    }
    TempSensor::SensorCore core(sensor_path, sensor);

    DBManager dbManager;
    dbManager.init(db_file);

    TempSensor::MqttSettings mqttSettings;

    mqttSettings.ID=iniParser.getValue(core::key::MQTT_ID).second;
    mqttSettings.server=iniParser.getValue(core::key::MQTT_SERVER).second;
    mqttSettings.port=std::stoi(iniParser.getValue(core::key::MQTT_PORT).second);//15786;
    mqttSettings.username=iniParser.getValue(core::key::MQTT_USERNAME).second;
    mqttSettings.password=iniParser.getValue(core::key::MQTT_PASSWORD).second;

    auto topic = iniParser.getValue(core::key::TOPIC1_TOPIC).second;

    std::cout << "Topic:" << topic << std::endl;

    TempSensor::MqttClient mqtt(mqttSettings, topic);

    auto mqttThread = std::thread([&mqtt](){
        if(mqtt.connect()){
            mqtt.loop();
        }else{
            std::cerr << "Mqtt failed to connect..." << std::endl;
        }
    });

    core.register_observer(dbManager);
    core.register_observer(mqtt);

    std::thread readSensorThread = readSensorTask.thread_run(std::bind(&TempSensor::SensorCore::readSensor, &core));

    if(history_topic != "N/A") {
        std::thread historyThread = postHistoryTask.thread_run([&mqtt, &dbManager, &history_topic]() {
            dbManager.getHistory(Serialize::historyQuery);
            mqtt.publish(history_topic, HistoryData::getInstance().getSerializeHistory(), 2);
            HistoryData::getInstance().clear();
        });

        historyThread.join();
    }else{
        std::cout << "History disabled" << std::endl;
    }

    mqttThread.join();
    readSensorThread.join();

    return 0;
}
