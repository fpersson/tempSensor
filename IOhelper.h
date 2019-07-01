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
