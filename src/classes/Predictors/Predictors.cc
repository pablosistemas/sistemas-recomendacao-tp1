#include "Predictors.h"

namespace Predictors {
    double SimpleRecommender::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >& userBased,
        std::map<std::string, std::map<std::string, double> >& similarItems,
        const std::string& user,
        const std::string& item)
    {
        double scores, totalSim; scores = totalSim = 0.0;
        for(auto &&userRating : userBased[user]) {
            for(auto &&itemRating : similarItems[item]) {
                if (userRating.first == itemRating.first) continue;
                scores += userRating.second.prediction * itemRating.second;
                totalSim += itemRating.second;
            }
        }
        return scores/totalSim;
    }

    double NeighborPrediction::operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >& userBased,
            std::vector<std::pair<std::string, double> >& topSimilarUsers,
            const std::string& user,
            const std::string& item)
    {
        double num, den; num = den = 0.0;
        for (auto it = topSimilarUsers.cbegin(); it != topSimilarUsers.cend(); it++) {
            if (userBased[user].count(item) == 0) continue;
            if (userBased[user][item] == 0) continue;
            num += userBased[user][item].prediction * it->second;
            den += it->second;
        }
        if (den == 0.0) return 0.0;
        return num/den;
    }
}
