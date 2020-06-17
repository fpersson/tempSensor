//
// Created by fredrik on 2020-06-17.
//

#include "History.h"

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
}
