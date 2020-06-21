//
// Created by fredrik on 2020-06-21.
//

#ifndef TEMPSENSOR_HISTORYDATA_H
#define TEMPSENSOR_HISTORYDATA_H

#include "History.h"

class HistoryData {
public:
    static HistoryData &getInstance(){
        static HistoryData instance;
        return instance;
    }

    void append(Serialize::HistoryPoint point){
        mHistory.push_back(point);
    }

    void clear(){
        mHistory.clear();
    }

    std::string getSerializeHistory(){
        return Serialize::history2Json(mHistory);
    }

    int size(){
        return mHistory.size();
    }

private:
    HistoryData(){;}
    Serialize::History mHistory;
};


#endif //TEMPSENSOR_HISTORYDATA_H
