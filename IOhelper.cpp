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
#include <fstream>

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
     *
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
