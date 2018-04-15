#include "Predictors.h"
#include "../Helpers/Helpers.h"

using namespace Helpers;

namespace Predictors {
    double SimpleRecommender::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >& userBasedMatrix,
        std::map<std::string, std::map<std::string, double> >& similarItems,
        const std::string& user,
        const std::string& item)
    {
        double scores, totalSim; scores = totalSim = 0.0;
        for(auto &&userRating : userBasedMatrix[user]) {
            for(auto &&itemRating : similarItems[item]) {
                if (userRating.first == itemRating.first) continue;
                scores += userRating.second.prediction * itemRating.second;
                totalSim += itemRating.second;
            }
        }
        return scores/totalSim;
    }

    double NeighborPrediction::operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >& userBasedMatrix,
            std::vector<std::pair<std::string, double> >& topSimilarUsers,
            const std::string& user,
            const std::string& item)
    {
        if (userBasedMatrix[user].count(item) > 0) { 
            return userBasedMatrix[user][item];
        }

        double num, den; num = den = 0.0;
        double avgUserA = getUserAverageScore(userBasedMatrix, user);
        for (auto it = topSimilarUsers.cbegin(); it != topSimilarUsers.cend(); it++) {
            if (userBasedMatrix[it->first].count(item) > 0) {
                double avgUserB = getUserAverageScore(userBasedMatrix, it->first);                
                if (userBasedMatrix[it->first][item] == 0) continue;
                else {
                    if (it->second > 0) {
                        num += it->second * (userBasedMatrix[it->first][item].prediction - avgUserB);
                        den += it->second;
                    }
                }
            }
        }
        if (den == 0.0) return double(0.0);
        return std::min(avgUserA + num/den, 10.0);
    }
}
