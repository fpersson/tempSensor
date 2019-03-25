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

#ifndef TEMPSENSOR_IOHELPER_H
#define TEMPSENSOR_IOHELPER_H


#include <string>
#include <vector>

namespace IO {

    using ReadResult = std::pair<bool, std::string>;
    using StringList = std::vector<std::string>;

    ReadResult readFromFile(const std::string &file);

    void writeToFile(const std::string &file, const std::string &data);

    StringList split(const std::string &string, char delimiter);

    /**
     * Accept any format strings
     * @param format
     * @return
     */
    std::string getCurrentTime(const std::string& format);

    /**
     * @param str
     * @return a string free from whitespace, does not remove newline or other tings
     */
    std::string trim(const std::string &str);

}//namespace


#endif //TEMPSENSOR_IOHELPER_H
