//
// Created by fredrik on 2019-03-25.
//

#include <iostream>
#include "IOhelper.h"
#include "Mqtt.h"

namespace TempSensor{
    Mqtt::Mqtt(TempSensor::MqttSettings &settings) :
                                    mosquittopp(settings.ID.c_str(), true),
                                    isConnected(false),
                                    mPendingData(""),
                                    mTopic(settings.topic){

        mosqpp::lib_init();
        int keepAlive=60;
        username_pw_set(settings.username.c_str(), settings.password.c_str());
        int result = connect(settings.server.c_str(), settings.port, keepAlive);
        loop_start();
        std::cout << "connecting result=" << result << std::endl;

    }

    void Mqtt::on_connect(int rc) {
        std::cout << "connected (" << rc << ")" << std::endl;
        if(rc == 0){
            subscribe(nullptr, mTopic.c_str());
            isConnected = true;
            notify(mPendingData); //make sure to send pending data asap we get connection
        }
    }

    void Mqtt::on_message(const struct mosquitto_message *message) {
        std::cout << "got message " << (char*)message->payload << std::endl;
    }

    void Mqtt::on_error() {
        std::cout << "A error..." << std::endl;
    }

    void Mqtt::notify(const std::string &data) {
        if(isConnected){
            std::cout << "Mqtt::notify: " << data << " sending..."<< std::endl;

            std::string sendData = "{\"date\": \"";
            sendData.append(IO::getCurrentTime("%a %d %B - %R"));
            sendData.append("\", \" temp\" : \"");
            sendData.append(data).append("\"}");

            publish(mTopic.c_str(), sendData);
            mPendingData = "";

        }else {
            std::cout << "Mqtt::notify: " << data << " waiting..."<< std::endl;
            mPendingData = data;
        }
    }

    void Mqtt::publish(const std::string& topic, const std::string& msg) {
        std::cout << "Mqtt::publish -m " << msg << " -t " << topic << std::endl;
        int rc = mosqpp::mosquittopp::publish(nullptr, topic.c_str(), msg.length(), msg.c_str(), 1, true);
    }
}//namespace