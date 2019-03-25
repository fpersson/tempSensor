//
// Created by fredrik on 2019-03-25.
//

#ifndef TEMPSENSOR_MQTT_H
#define TEMPSENSOR_MQTT_H

#include "mosquittopp.h"
#include "FObserver.h"


namespace TempSensor{
    struct MqttSettings{
        std::string ID;
        std::string server;
        int port;
        std::string username;
        std::string password;
        std::string topic;
    };

    class Mqtt : public mosqpp::mosquittopp, public FObserver::Observer{
    public:
        explicit Mqtt(MqttSettings& settings);
        void on_connect(int rc) override;
        void on_message(const struct mosquitto_message *message) override;
        void on_error() override;

        void notify(const std::string& data) override;

        /**
         * send msg with qos 1 and retain
         * @param topic
         * @param msg
         */
        void publish(const std::string& topic, const std::string& msg);
    private:
        bool isConnected;
        std::string mPendingData;
        std::string mTopic;
    };
}//namespace


#endif //TEMPSENSOR_MQTT_H
