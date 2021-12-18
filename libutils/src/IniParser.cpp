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


#include <fstream>
#include "IOhelper.h"
#include "IniParser.h"

namespace utils {
    IniParser::IniParser(const std::string &file) {
        parseFile(file);
    }

    IO::ReadResult IniParser::getValue(const std::string &key) {
        std::map<std::string, std::string>::iterator it;
        it = m_keyValues.find(key);

        if( it != m_keyValues.end() ){
            return std::make_pair(true, m_keyValues.find(key)->second);
        }else{
            return std::make_pair(false, "");
        }
    }


    ParseResult IniParser::parseSettings(const std::string &data) {
        bool success = false;
        Setting setting;
        if(!data.empty()){
            if (data.at(0) == ';' || data.at(0) == '[' || data.at(0) == '#') {
                //ignore comments
            } else {
                size_t found_char;
                found_char = data.find_first_of('=');
                if (found_char != std::string::npos) {
                    auto inline_comment = data.find_first_of('#');
                    if(inline_comment != std::string::npos){
                        auto len = inline_comment-(found_char+1);

                        auto key = IO::trim(data.substr(0, found_char));
                        auto value = IO::trim(data.substr(found_char + 1, len));

                        setting = std::pair<std::string, std::string>(key, value);
                        success = true;
                    }else {

                        auto key = IO::trim(data.substr(0, found_char));
                        auto value = IO::trim(data.substr(found_char + 1));

                        setting = std::pair<std::string, std::string>(key, value);
                        success = true;
                    }
                }
            }
        }
        return std::make_pair(success, setting);
    }

    void IniParser::parseFile(const std::string &file) {
        std::ifstream in(file);
        std::string line;
        std::string section;

        if(in.is_open()){
            while(getline(in, line)){
                auto result = isSection(IO::trim(line));
                if(result.first){
                    section = result.second;
                }else {
                    auto setting_result = parseSettings(line);
                    if(setting_result.first){
                        auto key = section;
                        key.append(setting_result.second.first);
                        auto value = setting_result.second.second;

                        m_keyValues.insert(std::make_pair(key, value));
                    }
                }
            }
        }else{
            std::cerr << " could not open: " << file << '\n';
        }

    }

    IO::ReadResult IniParser::isSection(const std::string &str) {
        bool is_section = false;
        std::string section;
        if (str.at(0) == '[') {
            is_section = true;
            auto last = str.find_last_not_of(']');
            section = str.substr(1, (last-1 +1)).append(".");
        }
        return std::make_pair(is_section, section);
    }
} //utils