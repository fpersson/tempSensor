/*
    Copyright (C) 2020 Fredrik Persson <fpersson.se@gmail.com>

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

#ifndef TEMPSENSOR_KEYS_H
#define TEMPSENSOR_KEYS_H

#include <iostream>

namespace core{
    namespace key {
        const std::string SENSOR = "SensorSettings.sensor";
        const std::string SENSOR_BASEPATH = "SensorSettings.base_path";
        const std::string SQLITE_DB = "SQLite.db_file";
        const std::string MQTT_ID = "Mqtt.ID";
        const std::string MQTT_SERVER = "Mqtt.server";
        const std::string MQTT_PORT = "Mqtt.port";
        const std::string MQTT_USERNAME = "Mqtt.username";
        const std::string MQTT_PASSWORD = "Mqtt.password";
        const std::string TOPIC1_TOPIC = "Topic1.topic";
        const std::string TOPIC1_INTERVAL = "Topic1.interval";
        const std::string TOPIC2_TOPIC = "Topic2.topic";
        const std::string TOPIC2_INTERVAL = "Topic2.interval";
    }
}

#endif //TEMPSENSOR_KEYS_H
