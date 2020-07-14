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

#include <mosquitto.h>
#include <atomic>
#include "../FObserver.h"


namespace TempSensor{
    struct MqttSettings{
        std::string ID;
        std::string server;
        int port;
        std::string username;
        std::string password;
    };


    class Mqtt{
    public:
        explicit Mqtt(MqttSettings& settings);
        ~Mqtt();

        /**
         * connect mqtt, get all paramaters from MqttSettings
         * @return
         */
        bool connect();

         /**
         * Set username and password for login, if username is null password is ignored
         */
        bool setUnamePwd(const std::string &username, const std::string &password);

        /**
         * called on accepted connection
         */
        virtual void onConnected() = 0;

        /**
         * @param topic
         * @param message
        */
        virtual void onMessage(std::string topic, std::string message) = 0;

        void subscribe(const std::string &topic, int qos);

        /**
         * @brief called on error message
         * @param errmsg
         */
        static void onError(const std::string &errmsg);

        /**
         * @param topic
         * @param msg
         */
        void publish(const std::string& topic, const std::string& msg, int qos);

        /**
         * Blocking loop
         */
        void loop();

        /**
         * disconnect the client
         */
        void close();

        /**
         * Cleanup mosquitto library. This call should be called before program termination
         */
        static void cleanup_library();

    private:
        MqttSettings mSettings;

        struct mosquitto *mosq = nullptr;
        std::atomic<bool> mRunning{};
    protected:
        bool isConnected;
        //std::string mTopic;
    };
}//namespace


#endif //TEMPSENSOR_MQTT_H
