//
// Created by fredrik on 2019-03-24.
//

#ifndef TEMPSENSOR_DBMANAGER_H
#define TEMPSENSOR_DBMANAGER_H

#include <iostream>
#include <memory>
#include <sqlite3.h>

#include "FObserver.h"

class DBManager : public FObserver::Observer {
public:
    DBManager(){;}
    ~DBManager();
    void notify(const std::string& data) override;
    bool init(const std::string &dbfile);

private:
    sqlite3* DB = nullptr;
    void createDatabase();
    bool exec(const std::string &query);

};


#endif //TEMPSENSOR_DBMANAGER_H
