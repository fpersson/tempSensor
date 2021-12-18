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


#include "DBManager.h"

DBManager::~DBManager() {
    std::cerr << "exit dbmanager\n";
    sqlite3_close(DB);
}

bool DBManager::init(const std::string &dbfile) {
    if(sqlite3_open(dbfile.c_str(), &DB) != SQLITE_OK){
        std::cerr << "Could not open: " << dbfile << '\n';
        return false;
    }
    createDatabase();
    return true;
}

bool DBManager::exec(const std::string &query) {
    int exit;
    char *errMsg;

    exit = sqlite3_exec(DB, query.c_str(), nullptr, nullptr, &errMsg);

    if (exit != SQLITE_OK) {
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

/**
 * @todo check if dbexist
 */
void DBManager::createDatabase() {

    std::string sql = "CREATE TABLE TEMPERATURE("
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "TEMP REAL NOT NULL,"
                      "TIMESTAMP DATETIME DEFAULT CURRENT_TIMESTAMP);";

    if(!exec(sql)){
        std::cerr << "Database exist\n";
    }
}

void DBManager::notify(const std::string &data) {

    if(DB != nullptr){
        std::string sql ="INSERT INTO TEMPERATURE (TEMP, TIMESTAMP) VALUES(";
        sql.append(data).append(", CURRENT_TIMESTAMP);");

        if(!exec(sql)){
            std::cerr << "Could not execute: " << sql << '\n';
        }
    }else{
        std::cerr << "No valid sqlite database\n";
    }
}

bool DBManager::exec(const std::string &query, int (*callback)(void *, int, char **, char **)) {
    int exit;
    char *errMsg;

    exit = sqlite3_exec(DB, query.c_str(), callback, nullptr, &errMsg);

    if (exit != SQLITE_OK) {
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool DBManager::getHistory(int(*callback)(void*, int, char **, char**)) {
    if(DB != nullptr){
        std::string sql ="select * from (select * from temperature order by ID desc limit 48) order by ID asc;";

        if(!exec(sql, callback)){
            std::cerr << "Could not execute: " << sql << '\n';
            return false;
        }
    }else{
        std::cerr << "No valid sqlite database\n";
    }
    return true;
}
