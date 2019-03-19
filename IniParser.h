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

#ifndef TEMPSENSOR_INIPARSER_H
#define TEMPSENSOR_INIPARSER_H
#include <iostream>
#include <map>

namespace utils {

    using InitResult = std::pair<bool, std::string>;
    /**
     * @class IniParser
     * @brief a simple parser for ini files, sections are not implemented (are ignored)
     */
    class IniParser {
    public:
        explicit IniParser(){;}
        /**
         * @param key
         * @return true and the value if the key exist, else false and a empty value
         */
        InitResult getValue(const std::string &key);
        void parseString(const std::string &data);
        void parseFile(const std::string &file);
    private:
        std::map<std::string, std::string> m_keyValues;
    };
} //utils


#endif //TEMPSENSOR_INIPARSER_H
