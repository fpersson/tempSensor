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

    InitResult IniParser::getValue(const std::string &key) {
        std::map<std::string, std::string>::iterator it;
        it = m_keyValues.find(key);

        if( it != m_keyValues.end() ){
            return std::make_pair(true, m_keyValues.find(key)->second);
        }else{
            return std::make_pair(false, "");
        }
    }


    void IniParser::parseString(const std::string &data) {
        if(!data.empty()){
            if (data.at(0) == ';' || data.at(0) == '[' || data.at(0) == '#') {
                ///@todo add support for sections if needed
            } else {
                size_t found_char;
                found_char = data.find_first_of("=");
                if (found_char != std::string::npos) {
                    auto inline_comment = data.find_first_of("#");
                    if(inline_comment != std::string::npos){
                        auto len = inline_comment-(found_char+1);

                        auto key = IO::trim(data.substr(0, found_char));
                        auto value = IO::trim(data.substr(found_char + 1, len));

                        m_keyValues.insert(std::pair<std::string, std::string>(key, value));
                    }else {

                        auto key = IO::trim(data.substr(0, found_char));
                        auto value = IO::trim(data.substr(found_char + 1));

                        m_keyValues.insert(std::pair<std::string, std::string>(key, value));
                    }
                }
            }
        }
    }

    void IniParser::parseFile(const std::string &file) {
        std::ifstream in(file);
        std::string line;

        if(in.is_open()){
            while(getline(in, line)){
                parseString(line);
            }
        }else{
            std::cerr << " could not open: " << file << '\n';
        }

    }
} //utils