#include "Predictors.h"

namespace Predictors {
    double SimpleRecommender::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >& userBased,
        std::map<std::string, std::map<std::string, double> >& similarItems,
        const std::string& user,
        const std::string& item)
    {
        double scores, totalSim;
        for(auto &&userRating : userBased[user]) {
            for(auto &&itemRating : similarItems[item]) {
                if (userRating.first == itemRating.first) continue;
                scores += userRating.second.prediction * itemRating.second;
                totalSim += itemRating.second;
            }
        }
        return scores/totalSim;
    }
} 