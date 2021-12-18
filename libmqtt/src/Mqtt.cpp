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
#include <sstream>
#include "IOhelper.h"
#include "Mqtt.h"

namespace TempSensor{

    static void on_connect(struct mosquitto *mosq_obj, void *obj, int rc) {
        std::cout << "on_connect called" << std::endl;

        (void)mosq_obj;
        Mqtt *mosq = (Mqtt*)obj;

        if(rc == 0) {
            mosq->onConnected();
        }else{
            std::stringstream ss ;
            ss << "Connection failed (Error code " << rc << ")";
            std::string msg = ss.str();
            mosq->onError(msg.c_str());
        };
    }

    static void on_message(struct mosquitto *mosq_obj, void *obj, const struct mosquitto_message *message) {
        (void)mosq_obj;
        Mqtt *mosq = (Mqtt*)obj;
        mosq->onMessage(std::string((char*)message->topic) , std::string((char*)message->payload));
    }

    [[maybe_unused]]
    static int hpp_pw_callback(char *buf, int size, int rwflag, void *userdata) {
        (void)buf;
        (void)size;
        (void)rwflag;
        (void)userdata;
        return -1;
    }

    [[maybe_unused]]
    static void log_callback(struct mosquitto *m, void *v, int i, const char *c){
        std::cerr << "DEBUG: " << c << std::endl;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Mqtt::Mqtt(TempSensor::MqttSettings &settings) : mSettings(settings), isConnected(false){
        mosquitto_lib_init();
        mosq = mosquitto_new(nullptr, true, this);

        if(this->mosq == nullptr){
            std::cerr << "Error creating mosquitto instance" << std::endl;
        }

        if(setUnamePwd(settings.username.c_str(), settings.password.c_str())){
            mosquitto_connect_callback_set(this->mosq, &on_connect);
            mosquitto_message_callback_set(this->mosq, &on_message);
#ifdef DEBUGMODE
            mosquitto_log_callback_set(mosq, &log_callback);
#endif
        }else{
            std::cerr << "Username/password invalid - not connected" << std::endl;
        }
    }

    void Mqtt::publish(const std::string& topic, const std::string& msg, int qos) {
        std::cout << "Mqtt::publish -m " << msg << " -t " << topic << std::endl;

        const char *payload = msg.c_str();
        const int len = (int)msg.size();

        int ret = mosquitto_publish(mosq, nullptr, topic.c_str(), len, (const void*)payload, qos, true);
        if(ret != MOSQ_ERR_SUCCESS){
            std::cerr << "Publish error" << std::endl;
        }
    }

    void Mqtt::onMessage(std::string topic, std::string message) {

    }

    void Mqtt::onError(const std::string &errmsg) {
        std::cerr << "Mqtt Error - " << errmsg << std::endl;
    }

    bool Mqtt::setUnamePwd(const std::string &username, const std::string &password) {
        return !(mosquitto_username_pw_set(mosq, username.c_str(), password.c_str()) != MOSQ_ERR_SUCCESS);
    }

    void Mqtt::loop() {
        if(mosq == nullptr){
            std::cout << "Mqtt::loop - nullptr error" << std::endl;
        }
        int rc = mosquitto_loop_forever(mosq, -1, 1);
        std::cout << "exit loop (" << rc << ")" << std::endl;

        if(rc == MOSQ_ERR_SUCCESS){
            std::cout << "Started ok" << std::endl;
        }else if(rc == MOSQ_ERR_NO_CONN){
            std::cout << "No connection" << std::endl;
        }else if(rc == MOSQ_ERR_CONN_REFUSED){
            std::cout << "Connection refused" << std::endl;
        }else if(rc == MOSQ_ERR_PROTOCOL){
            std::cout << "Protocol wrong" << std::endl;
        }else if(rc == MOSQ_ERR_CONN_LOST){
            std::cout << "Connection lost" << std::endl;
        }else if(rc == MOSQ_ERR_NOMEM){
            std::cout << "No memory" << std::endl;
        }else if(rc == MOSQ_ERR_INVAL){
            std::cout << "Inval error" << std::endl;
        }else if(rc == MOSQ_ERR_ERRNO ) {
            std::cout << "Errno" << std::endl;
        }else if(rc == MOSQ_ERR_TLS){
            std::cout << "TSL Error" << std::endl;
        } else {
            std::cout << "wtf?" << std::endl;
        }
    }


    void Mqtt::close() {
        mRunning = false;
        mosquitto_disconnect(mosq);
    }

    void Mqtt::cleanup_library() {
        mosquitto_lib_cleanup();
    }

    void Mqtt::subscribe(const std::string &topic, const int qos) {
        int ret = mosquitto_subscribe(mosq, NULL, topic.c_str(), qos);
        if(ret != MOSQ_ERR_SUCCESS){
            std::cout << "Subscribe error" << std::endl;
        }
    }

    Mqtt::~Mqtt() {
        cleanup_library();
        mosquitto_destroy(mosq);
    }

    bool Mqtt::connect() {
        bool connection_state = false;
        int ret = mosquitto_connect(mosq, mSettings.server.c_str(), mSettings.port, 30);
        if(ret != MOSQ_ERR_SUCCESS){
            connection_state = true;
        }else{
            std::cerr << "Mqtt::connected..." << std::endl;
            isConnected = true;
        }

        return connection_state;
    }
}//namespace
