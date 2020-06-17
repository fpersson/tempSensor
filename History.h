//
// Created by fredrik on 2020-06-17.
//

#ifndef TEMPSENSOR_HISTORY_H
#define TEMPSENSOR_HISTORY_H

#include <string>
#include <vector>

namespace Serialize {
    const std::string timestamp = "\"TIMESTAMP\":\""; //json key
    const std::string id = "\"ID\":\""; //json key
    const std::string temp = "\"TEMP\":\""; //json key

    struct HistoryPoint {
        std::string timestamp;
        std::string ID;
        std::string temp;
    };
    using History = std::vector<HistoryPoint>;

    /**
     * @param history
     * @return a serialized history
     */
    std::string history2Json(const History &history);

} //namespace;

#endif //TEMPSENSOR_HISTORY_H
