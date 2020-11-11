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


#ifndef TEMPSENSOR_INIPARSER_H
#define TEMPSENSOR_INIPARSER_H
#include <iostream>
#include <map>

#include "IOhelper.h"

namespace utils {
    /**
     * Setting.key Setting.value
     */
    using Setting = std::pair<std::string, std::string>;
    using ParseResult = std::pair<bool, Setting>;

    /**
     * @class IniParser
     * @brief a simple parser for ini files, sections are not implemented (are ignored)
     */
    class IniParser {
    public:
        explicit IniParser(){;}
        explicit IniParser(const std::string &file);
        /**
         * @param key
         * @return true and the value if the key exist, else false and a empty value
         */
        IO::ReadResult getValue(const std::string &key);
        void parseFile(const std::string &file);

    private:
        IO::ReadResult isSection(const std::string &str);
        ParseResult parseSettings(const std::string &data);

        std::map<std::string, std::string> m_keyValues;
    };
} //utils


#endif //TEMPSENSOR_INIPARSER_H
