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
