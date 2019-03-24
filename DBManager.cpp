//
// Created by fredrik on 2019-03-24.
//

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
    int exit = 0;
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
#ifdef DEBUGMODE
        std::cout << sql << std::endl;
#endif
        if(!exec(sql)){
            std::cerr << "Could not execute: " << sql << '\n';
        }
    }else{
        std::cerr << "No valid sqlite database\n";
    }
}
