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
#include "mqtt/Mqtt.h"
#include "History.h"
#include "HistoryData.h"
#include "MqttClient.h"

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

    if(iniParser.getValue("SensorSettings.sensor").first){
        sensor = iniParser.getValue("SensorSettings.sensor").second;
    }else{
        std::cerr << "no sensor defined in " << ini_file << '\n';
    }

    if(iniParser.getValue("Topic1.interval").first){
        interval = std::stol(iniParser.getValue("Topic1.interval").second);
    }else{
        std::cerr << "no interval defined in " << ini_file << " using default 1 minute\n";
    }

    if(iniParser.getValue("SQLite.db_file").first){
        db_file = iniParser.getValue("SQLite.db_file").second;
    }else{
        std::cerr << "no db_file defined in " << ini_file << '\n';
    }

    if(iniParser.getValue("Topic2.topic").first){
        history_topic = iniParser.getValue("Topic2-topic").second;
    }else{
        std::cerr << "no Topic2.topic defined in " << ini_file << '\n';
    }

    TempSensor::TimerTask readSensorTask(interval);
    TempSensor::TimerTask postHistoryTask(interval); //@todo, set its own interval

    TempSensor::SensorCore core(sensor);

    DBManager dbManager;
    dbManager.init(db_file);

    TempSensor::MqttSettings mqttSettings;

    mqttSettings.ID=iniParser.getValue("Mqtt.ID").second;
    mqttSettings.server=iniParser.getValue("Mqtt.server").second;
    mqttSettings.port=std::stoi(iniParser.getValue("Mqtt.port").second);//15786;
    mqttSettings.username=iniParser.getValue("Mqtt.username").second;
    mqttSettings.password=iniParser.getValue("Mqtt.password").second;

    auto topic = iniParser.getValue("Topic1.topic").second;

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
#ifdef DEBUGMODE
            std::cout << HistoryData::getInstance().getSerializeHistory() << std::endl;
#endif
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
