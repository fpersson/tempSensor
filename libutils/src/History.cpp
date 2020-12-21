//
// Created by fredrik on 2020-06-17.
//

#include "History.h"
#include "HistoryData.h"

namespace Serialize {
    std::string history2Json(const History &history) {
        std::string begin = "{\"data\":[";
        std::string end = "]}";

        std::string result;
        result.append(begin);

        for(int i = 0; i <history.size(); ++i){
            std::string tmp;
            tmp.append("{");
            tmp.append(timestamp);
            tmp.append(history.at(i).timestamp);
            tmp.append("\",");
            tmp.append(id);
            tmp.append(history.at(i).ID);
            tmp.append("\",");
            tmp.append(temp);
            tmp.append(history.at(i).temp);
            tmp.append("\"}");
            if(i < history.size()-1){
                tmp.append(",");
            }
            result.append(tmp);
        }

        result.append(end);
        return result;
    }

    int historyQuery(void *data, int argc, char **argv, char **azColName){
#ifdef DEBUGMODE
        int i;
        for(i = 0; i<argc; i++){
            std::cout << "i=" << i << " " << azColName[i] << "=" << argv[i] << std::endl;
        }
#endif

        HistoryPoint point;
        point.ID=argv[0];
        point.temp=argv[1];
        point.timestamp=argv[2];
        HistoryData::getInstance().append(point);

        return 0;
    }
}
