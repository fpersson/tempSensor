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
#include <fstream>
#include <chrono>
#include <iomanip>

#include "IOhelper.h"

namespace IO{

    void writeToFile(const std::string &file, const std::string &data){
        std::ofstream stream;
        stream.open(file);
        stream << data;
        stream.flush();
        stream.close();
    }

    /**
     * @param file
     * @return true and a string if we have valid data, and false and a empty string if we dont have anything
     */
    ReadResult readFromFile(const std::string &file){
        std::string data;
        std::string line;
        std::ifstream stream(file);
        if(stream.is_open()){
            while(getline(stream, line)){
                data.append(line);
                data.append("\n");
            }
        }else{
            std::cerr << "could not open: " << file << '\n';
            return std::make_pair(false, "");
        }
        return std::make_pair(true, data);
    }

    std::string getCurrentTime(const std::string& format){
        auto now = std::chrono::system_clock::now();
        auto current = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;

        ss << std::put_time(std::localtime(&current), format.c_str());
        return ss.str();
    }

    StringList split(const std::string &string, char delimiter){
        StringList ret;
        size_t found_char = string.find(delimiter);
        size_t start_pos = 0;

        while(found_char != std::string::npos){
            ret.emplace_back( string.substr(start_pos, found_char - start_pos));
            start_pos = found_char + 1;
            found_char = string.find(delimiter, start_pos);
        }
        ret.emplace_back(string.substr(start_pos, std::min(found_char, string.size()) -start_pos +1 ));

        return ret;
    }

    std::string trim(const std::string &str){
        auto first = str.find_first_not_of(' ');

        if(std::string::npos == first){
            return str;
        }

        auto last = str.find_last_not_of(' ');
        return str.substr(first, (last-first +1));
    }

}//namespace
