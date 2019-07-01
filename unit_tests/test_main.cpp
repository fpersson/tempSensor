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
#include "../IOhelper.h"
#include "../IniParser.h"
#include "../optional.h"

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

utils::option<std::string> getValue1(){
    return {"Hello, world"};
}


utils::option<std::string> getValue2(){
    return utils::option<std::string>::none();
}

TEST(myOptional, optional){
    EXPECT_EQ("Hello, world", *getValue1());
    EXPECT_FALSE(getValue2());
}
