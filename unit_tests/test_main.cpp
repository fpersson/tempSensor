/*
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA  02110-1301, USA.

    ---
    Copyright (C) 2019, Fredrik Persson <fpersson.se@gmail.com>
 */

#include <iostream>
#include <map>
#include "gtest/gtest.h"
#include "../IOhelper.h"
#include "../IniParser.h"

TEST(inifile, stringsplit){
    utils::IniParser iniParser;

    iniParser.parseString("; this is a comments");
    iniParser.parseString("# this is a comments");
    iniParser.parseString("[section]");
    iniParser.parseString("foo=bar");
    iniParser.parseString("test=apa #inline comment");
    iniParser.parseString("");
    utils::InitResult result = iniParser.getValue("foo");
    EXPECT_TRUE(result.first);
    EXPECT_EQ("bar",  result.second);

    utils::InitResult result_test = iniParser.getValue("test");
    EXPECT_TRUE(result_test.first);
    EXPECT_EQ("apa", result_test.second);

    utils::InitResult resulterr = iniParser.getValue("bar");
    EXPECT_FALSE(resulterr.first);
}

TEST(initfile, readfile){
    utils::IniParser iniParser;

    iniParser.parseFile("./testdata/settings.ini");

    utils::InitResult sensor_id = iniParser.getValue("sensor");
    EXPECT_TRUE(sensor_id.first);
    EXPECT_EQ("28-0417a2f482ff", sensor_id.second);

    utils::InitResult url = iniParser.getValue("url");
    EXPECT_TRUE(url.first);
    EXPECT_EQ("https://testing-c408e.firebaseio.com/sensors/testing/current.json", url.second);

    utils::InitResult token = iniParser.getValue("token");
    EXPECT_TRUE(token.first);
    EXPECT_EQ("AIzaSyDBE1KqXaAvicpGklTBRP0ZvYoBJXG5PoI", token.second);

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
