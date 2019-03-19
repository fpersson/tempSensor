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

#ifndef TEMPSENSOR_CURLFIREBASE_H
#define TEMPSENSOR_CURLFIREBASE_H

#include "FObserver.h"

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up);

class CurlFirebase : public FObserver::Observer {
public:
    explicit CurlFirebase(std::string Url, std::string token);
    void notify(const std::string& data) override;

private:
    std::string url;
    std::string access_token;
};


#endif //TEMPSENSOR_CURLFIREBASE_H
