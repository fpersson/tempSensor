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


#ifndef TEMPSENSOR_DBMANAGER_H
#define TEMPSENSOR_DBMANAGER_H

#include <iostream>
#include <memory>
#include <sqlite3.h>

#include "FObserver.h"

class DBManager : public FObserver::Observer {
public:
    DBManager()= default;
    ~DBManager();
    void notify(const std::string& data) override;
    bool init(const std::string &dbfile);

    bool getHistory(int(*callback)(void*, int, char **, char**));

private:
    sqlite3* DB = nullptr;
    void createDatabase();
    bool exec(const std::string &query);

    bool exec(const std::string &query, int(*callback)(void*, int, char **, char**));

};


#endif //TEMPSENSOR_DBMANAGER_H
