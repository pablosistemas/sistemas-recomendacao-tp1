#include "../TopMatches/TopMatches.h"
#include "../Predictors/Predictors.h"
#include "../Similarity/Similarity.h"
#include "../Helpers/Helpers.h"
#include "Algorithms.h"

#include <algorithm>
#include <iostream>
#include <random>

using namespace Recommender;
using namespace Similarity;
using namespace Predictors;
using namespace Helpers;

namespace Algorithms {
    void ItemToItem::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >& itemBasedMatrix,
        std::map<std::string, std::map<std::string, ItemPrediction> >& userBasedMatrix,
        std::map<std::string, std::map<std::string, double> >& itemSimilarity,
        RatingList &targets, int K, int P
    ) {
        /**
        * Why Weibull?
        * In cases when there is no items similar to the current item under
        * evaluation it is needed to randomly choose a rating value to it.
        * The best way I found to estimate this value is using the same
        * training data' rating's distribution.
        * 
        * R code:
        *   num.items <- 5000
        *   sampling <- sample(length(data$Prediction))[1:num.items]
        *   samples <- data$Prediction[sampling]
        *   barplot(table(samples))
        *   library(MASS)
        *   fit.w <- fitdistr(samples, "weibull")
        *   shape <- fit.w$estimate[1] # 4.591694
        *   scale <- fit.w$estimate[2] # 7.940204
        *   qqplot(samples, rweibull(1000, shape, scale))
        */
        std::default_random_engine gen;
        // std::weibull_distribution<double> dist(4.591694, 7.940204);
        std::weibull_distribution<double> dist(4.700021, 7.960964);

        std::cout << "UserId:ItemId,Prediction" << std::endl;
        for (auto it = targets.ratings.cbegin(); it != targets.ratings.cend(); it++){
            double num, den; num = den = 0.0;
            for(auto iti = itemSimilarity[it->itemId].cbegin(); iti != itemSimilarity[it->itemId].cend(); iti++) {
                if (userBasedMatrix[it->userId].count(iti->first) == 0) continue;
                num += iti->second * userBasedMatrix[it->userId][iti->first];
                den += std::abs(iti->second);
            }

            if (den != 0.0) {
                std::cout << it->userId << ":" << it->itemId << "," << num/den << std::endl;
            } else {
                double rating = 0.0;
                if (userBasedMatrix[it->userId].size() > 0) {
                    rating = getUserAverageScore(userBasedMatrix, it->userId);
                } else {
                    rating = std::max(0, std::min((int)std::floor(dist(gen)), 10));
                }
                std::cout << it->userId << ":" << it->itemId << "," << rating << std::endl;
            }
        }
    }

    void UserToUser::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >&userBasedMatrix,
        std::map<std::string, std::map<std::string, ItemPrediction> >&itemBasedMatrix,
        RatingList &targets, int K, int P, bool randomize)
    {
        std::default_random_engine gen;
        std::weibull_distribution<double> dist(4.591694, 7.940204);

        for (auto it = targets.ratings.cbegin(); it != targets.ratings.cend(); it++){
            auto topSimilarUsers = TopMatches()(
                userBasedMatrix,
                itemBasedMatrix,
                it->userId,
                Pearson(), K, P, randomize);
            auto prediction = NeighborPrediction()(userBasedMatrix, topSimilarUsers, it->userId, it->itemId);
            if (prediction == 0.0) {
                prediction = std::max(0, std::min((int)std::floor(dist(gen)), 10));
            }
            std::cout << it->userId << ":" << it->itemId << "," << prediction << std::endl;
        }
    }

    // FIXME: test
    void Hybrid::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >&userBasedMatrix,
        std::map<std::string, std::map<std::string, ItemPrediction> >&itemBasedMatrix,
        std::map<std::string, std::map<std::string, double> >&similarUsers,
        std::map<std::string, std::map<std::string, double> >&itemSimilarity,
        RatingList &targets,
        double* sumRating, int* numItems, int K, int P)
    {
        std::default_random_engine gen;
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        // test item based, if there is no correlation, go with user based
        for (auto it = targets.ratings.cbegin(); it != targets.ratings.cend(); it++){
            double num, den; 
            num = den = 0.0;

            for(auto iti = itemSimilarity[it->itemId].cbegin(); iti != itemSimilarity[it->itemId].cend(); iti++) {
                if (userBasedMatrix[it->userId].count(iti->first) == 0) continue;
                num += iti->second * userBasedMatrix[it->userId][iti->first];
                den += std::abs(iti->second);
            }

            if (den != 0.0) {
                std::cout << it->userId << ":" << it->itemId << "," << num/den << std::endl;
                (*sumRating) += num/den;
            } else {
                std::for_each(similarUsers[it->userId].cbegin(), similarUsers[it->userId].cend(),
                [&](std::pair<std::string, double> user){
                    if (userBasedMatrix[user.first].count(it->itemId) > 0)  {
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

                if (den != 0) {
                    std::cout << it->userId << ":" << it->itemId << "," << num/den << std::endl;
                    (*sumRating) += num/den;
                } else {
                    auto rating = ( dist(gen) * 10.0 );
                    (*sumRating) += rating;
                    std::cout << it->userId << ":" << it->itemId << "," << rating << std::endl;
                }
            }
            (*numItems)++;
        }
    }
}