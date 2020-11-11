/*
    Copyright (C) 2020, Fredrik Persson <fpersson.se@gmail.com>

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


#ifndef TEMPSENSOR_MQTTCLIENT_H
#define TEMPSENSOR_MQTTCLIENT_H

#include "Mqtt.h"
#include "FObserver.h"

namespace TempSensor {
    class MqttClient : public Mqtt, public FObserver::Observer {
    public:
        MqttClient(MqttSettings &settings, const std::string &notify_topic) : Mqtt(settings), mPendingData(""), mNotifyTopic(notify_topic){;}

        void onConnected() override;

        void onMessage(std::string topic, std::string message) override;

        void notify(const std::string& data) override;
    private:
        std::string mPendingData;
        std::string mNotifyTopic;
    };
}


#endif //TEMPSENSOR_MQTTCLIENT_H
