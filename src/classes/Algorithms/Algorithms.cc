#include "Algorithms.h"
#include "../RatingList/RatingList.h"
#include "../TopMatches/TopMatches.h"
#include "../Predictors/Predictors.h"
#include "../Similarity/Similarity.h"

#include <iostream>
#include <algorithm>

using namespace Recommender;
using namespace Similarity;
using namespace Predictors;

namespace Algorithms {
    void ItemToItem::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >& itemBasedMatrix,
        std::map<std::string, std::map<std::string, ItemPrediction> >& userBasedMatrix,
        std::map<std::string, std::map<std::string, double> >& itemSimilarity,
        RatingList &targets,
        int K, int P
    ) {
        std::cout << "UserId:ItemId,Prediction" << std::endl;
        for (auto it = targets.ratings.cbegin(); it != targets.ratings.cend(); it++){
            // std::vector<std::pair<std::string, double> > topSimilars;
            // for (auto itm = itemSimilarity[it->itemId].cbegin();
            //         itm != itemSimilarity[it->itemId].cend(); itm++) {
            //             topSimilars.push_back(*itm);
            // }
            // auto predict = NeighborPrediction()(
            //     itemBasedMatrix,
            //     topSimilars,
            //     it->userId,
            //     it->itemId); 

            double num, den; num = den = 0.0;
            for(auto iti = itemSimilarity[it->itemId].cbegin(); iti != itemSimilarity[it->itemId].cend(); iti++) {
                if (userBasedMatrix[it->userId].count(iti->first) == 0) continue;
                num += iti->second * userBasedMatrix[it->userId][iti->first];
                den += std::abs(iti->second);
            }
            std::cout << it->userId << ":" << it->itemId << "," << num/den << std::endl;
        }
    }

    void UserToUser::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >&userBasedMatrix,
        std::map<std::string, std::map<std::string, double> >&similarUsers,
        RatingList &targets,
        int K, int P)
    {
        for (auto it = targets.ratings.cbegin(); it != targets.ratings.cend(); it++){
            auto num = 0.0;
            auto den = 0.0;
            std::for_each(similarUsers[it->userId].cbegin(), similarUsers[it->userId].cend(),
            [&](std::pair<std::string, double> user){
                if (userBasedMatrix[user.first].count(it->itemId) >= 0)  {
                    auto avgUserB = std::accumulate(
                        userBasedMatrix[user.first].cbegin(),
                        userBasedMatrix[user.first].cend(),
                        0.0,
                        [](double acc, auto itemB) {
                            return acc + itemB.second.prediction;
                        }
                    );
                    avgUserB = avgUserB/userBasedMatrix[user.first].size();
                    num += similarUsers[it->userId][user.first] * (userBasedMatrix[user.first][it->itemId].prediction - avgUserB);
                    den += std::abs(similarUsers[it->userId][user.first]);
                }
            });

            auto avgUserA = std::accumulate(
                userBasedMatrix[it->userId].cbegin(),
                userBasedMatrix[it->userId].cend(),
                0.0,
                [](double acc, auto itemA) {
                    return acc + itemA.second.prediction;
                }
            );
            avgUserA = avgUserA/userBasedMatrix[it->userId].size();
            std::cout << it->userId << ":" << it->itemId << "," << avgUserA + num/den << std::endl;
        }
    }
}