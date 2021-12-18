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
#include <map>
#include "gtest/gtest.h"
#include "IOhelper.h"
#include "IniParser.h"
#include "History.h"
#include "Keys.h"

TEST(inifile, readfile){
    utils::IniParser iniParser;

    iniParser.parseFile("../testdata/settings.ini");

    IO::ReadResult sensor_id = iniParser.getValue(core::key::SENSOR);
    EXPECT_TRUE(sensor_id.first);
    EXPECT_EQ("28-0417a2f482ff", sensor_id.second);
}

TEST(inifile, read_full){
    utils::IniParser iniParser;

    iniParser.parseFile("../testdata/settings.ini");

    IO::ReadResult sensor_id = iniParser.getValue(core::key::SENSOR);
    EXPECT_TRUE(sensor_id.first);
    EXPECT_EQ("28-0417a2f482ff", sensor_id.second);

    IO::ReadResult sensor_path = iniParser.getValue(core::key::SENSOR_BASEPATH);
    EXPECT_FALSE(sensor_path.first);

    IO::ReadResult db_file = iniParser.getValue(core::key::SQLITE_DB);
    EXPECT_TRUE(db_file.first);
    EXPECT_EQ("./testdata/temperature.db", db_file.second);

    IO::ReadResult mqtt_id = iniParser.getValue(core::key::MQTT_ID);
    EXPECT_TRUE(mqtt_id.first);
    EXPECT_EQ("foo1", mqtt_id.second);

    IO::ReadResult mqtt_server = iniParser.getValue(core::key::MQTT_SERVER);
    EXPECT_TRUE(mqtt_server.first);
    EXPECT_EQ("m24.cloudmqtt.com", mqtt_server.second);

    IO::ReadResult mqtt_port = iniParser.getValue(core::key::MQTT_PORT);
    EXPECT_TRUE(mqtt_port.first);
    EXPECT_EQ("15786", mqtt_port.second);

    IO::ReadResult mqtt_uname = iniParser.getValue(core::key::MQTT_USERNAME);
    EXPECT_TRUE(mqtt_uname.first);
    EXPECT_EQ("test", mqtt_uname.second);

    IO::ReadResult mqtt_pass = iniParser.getValue(core::key::MQTT_PASSWORD);
    EXPECT_TRUE(mqtt_pass.first);
    EXPECT_EQ("test", mqtt_pass.second);

    IO::ReadResult mqtt_topic_1 = iniParser.getValue(core::key::TOPIC1_TOPIC);
    EXPECT_TRUE(mqtt_topic_1.first);
    EXPECT_EQ("playground", mqtt_topic_1.second);

    IO::ReadResult mqtt_interval_1 = iniParser.getValue(core::key::TOPIC1_INTERVAL);
    EXPECT_TRUE(mqtt_interval_1.first);
    EXPECT_EQ("1", mqtt_interval_1.second);

    IO::ReadResult mqtt_topic_2 = iniParser.getValue(core::key::TOPIC2_TOPIC);
    EXPECT_TRUE(mqtt_topic_2.first);
    EXPECT_EQ("playground_history", mqtt_topic_2.second);

    IO::ReadResult mqtt_interval_2 = iniParser.getValue(core::key::TOPIC2_INTERVAL);
    EXPECT_TRUE(mqtt_interval_2.first);
    EXPECT_EQ("1", mqtt_interval_2.second);

}

TEST(functions, trim){
    std::string untrimmed_end = "end ";
    std::string untrimmed_begin = " begin";
    std::string untrimmed = " this is the end ";
    std::string last = "This is correct";

    EXPECT_EQ("end", IO::trim(untrimmed_end));
    EXPECT_EQ("begin", IO::trim(untrimmed_begin));
    EXPECT_EQ("this is the end", IO::trim(untrimmed));
    EXPECT_EQ(last, IO::trim(last));
}

TEST(json, generate_one){
    Serialize::History history;
    Serialize::HistoryPoint h1;

    h1.timestamp = "2019-04-19 21:18:52";
    h1.ID = "916";
    h1.temp = "7.62";
    history.emplace_back(h1);

    EXPECT_EQ("{\"data\":[{\"TIMESTAMP\":\"2019-04-19 21:18:52\",\"ID\":\"916\",\"TEMP\":\"7.62\"}]}",Serialize::history2Json(history));
}

TEST(json, generate_multiple){
    Serialize::History history;
    Serialize::HistoryPoint h1;

    h1.timestamp = "2019-04-19 21:18:52";
    h1.ID = "916";
    h1.temp = "7.62";
    history.emplace_back(h1);

    Serialize::HistoryPoint h2;
    h2.timestamp = "2019-04-19 20:48:51";
    h2.ID = "915";
    h2.temp = "8.5";
    history.emplace_back(h2);

    Serialize::HistoryPoint h3;
    h3.timestamp = "2019-04-19 21:18:52";
    h3.ID = "916";
    h3.temp = "7.62";
    history.emplace_back(h3);

    EXPECT_EQ("{\"data\":[{\"TIMESTAMP\":\"2019-04-19 21:18:52\",\"ID\":\"916\",\"TEMP\":\"7.62\"},{\"TIMESTAMP\":\"2019-04-19 20:48:51\",\"ID\":\"915\",\"TEMP\":\"8.5\"},{\"TIMESTAMP\":\"2019-04-19 21:18:52\",\"ID\":\"916\",\"TEMP\":\"7.62\"}]}",Serialize::history2Json(history));
}
