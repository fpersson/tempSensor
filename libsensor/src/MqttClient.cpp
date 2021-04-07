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

#include "MqttClient.h"
#include "IOhelper.h"

void TempSensor::MqttClient::notify(const std::string &data) {
    if(isConnected){
#ifdef DEBUGMODE
        std::cout<< "Mqtt::notify: " << data << " sending..."<< std::endl;
#endif
        std::string sendData = R"({"date": ")";
        sendData.append(IO::getCurrentTime("%a %d %B - %R"));
        sendData.append(R"(", "temp" : ")");
        sendData.append(data).append("\"}");

        publish(mNotifyTopic, sendData, 2);
        mPendingData = "";
    }else {
#ifdef DEBUGMODE
        std::cout << "Mqtt::notify: " << data << " waiting..."<< std::endl;
#endif
        mPendingData = data;
    }
}

void TempSensor::MqttClient::onConnected() {
    std::cout << "Mqtt Connected..." << std::endl;
#ifdef DEBUGMODE
    subscribe("testing", 2);
#endif

    notify(mPendingData); //make sure to send pending data asap we get connection
}

void TempSensor::MqttClient::onMessage(std::string topic, std::string message) {
    //not implemented
}
