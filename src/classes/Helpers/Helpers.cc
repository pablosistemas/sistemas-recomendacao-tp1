#include "./Helpers.h"
#include "time.h"

#include <iostream>

namespace Helpers {
    double getUserAverageScore(
        std::map<std::string, std::map<std::string, ItemPrediction> >&userBasedMatrix,
        std::string user)
    {
        auto avgUser = std::accumulate(
            userBasedMatrix[user].cbegin(),
            userBasedMatrix[user].cend(),
            0.0,
            [](double acc, auto item) {
                return acc + item.second.prediction;
            }
        );
        return avgUser/userBasedMatrix[user].size();
    }
}