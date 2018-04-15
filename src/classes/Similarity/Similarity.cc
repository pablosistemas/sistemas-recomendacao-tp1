#include "../Helpers/Helpers.h"
#include "./Similarity.h"
#include <algorithm>
#include <cmath>

using namespace Helpers;

namespace Similarity{
    double Pearson::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >& userBasedMatrix,
        std::map<std::string, std::map<std::string, ItemPrediction> >& itemBasedMatrix,
        const std::string& userId1,
        const std::string& userId2)
    {
        std::map<std::string, int> ratingsInCommon;
        std::for_each(userBasedMatrix[userId1].cbegin(), userBasedMatrix[userId1].cend(),
            [&] (std::pair<std::string,ItemPrediction> item){
                auto iti = userBasedMatrix[userId2].find(item.first);
                if (iti != userBasedMatrix[userId2].end()) {
                    ratingsInCommon[item.first] = 1;
                }
            });
        auto n = ratingsInCommon.size();
        if (n == 0) return 0;

        //double sum1, sum2, sum1Sq, sum2Sq, pSum;
        //sum1 = sum2 = sum1Sq = sum2Sq = pSum = 0;
        double num, den, sum1Sq, sum2Sq; sum1Sq = sum2Sq = num = den = 0.0;
        auto avgUser1 = Helpers::getUserAverageScore(userBasedMatrix, userId1);
        auto avgUser2 = Helpers::getUserAverageScore(userBasedMatrix, userId2);

        std::for_each(
            ratingsInCommon.cbegin(),
            ratingsInCommon.cend(),
            [&](std::pair<std::string, int>const & itm) {
                auto d1 = userBasedMatrix[userId1][itm.first].prediction - avgUser1;
                auto d2 = userBasedMatrix[userId2][itm.first].prediction - avgUser2;
                num += d1 * d2;
                sum1Sq += pow(d1, 2);
                sum2Sq += pow(d2, 2);
        });

        den = sqrt(sum1Sq) * sqrt(sum2Sq);
        if (den == 0.0) return double(0);
        return num/den;
    }

    double Distance::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >&userBasedMatrix,
        std::map<std::string, std::map<std::string, ItemPrediction> >&itemBasedMatrix,
        const std::string& user1,
        const std::string& user2)
    {
        std::map<std::string, double> sim;
        for (auto &&item : userBasedMatrix[user1]){
            if (userBasedMatrix[user2].count(item.first) == 1) {
                sim.insert(std::pair<std::string, double>(item.first, 1));
            }
        }

        if (sim.size() == 0) return 0;
        double sum = 0.0;
        std::for_each(sim.cbegin(), sim.cend(), [&](std::pair<std::string, double>const& item){
            sum += pow(userBasedMatrix[user1][item.first] - userBasedMatrix[user2][item.first], 2);
        });
        auto sum1 = 1.0/(1.0 + sqrt(sum));
        return sum1;
    }

    double Cosine::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >&itemBasedmatrix,
        std::map<std::string, std::map<std::string, ItemPrediction> >&userBasedmatrix,
        const std::string& item1,
        const std::string& item2)
    {
        std::map<std::string, double> sim;
        for (auto &&item : itemBasedmatrix[item1]){
            if (itemBasedmatrix[item2].count(item.first) == 1) {
                sim.insert(std::pair<std::string, double>(item.first, 1));
            }
        }

        if (sim.size() == 0) return 0;
        double num, den1, den2;
        num = den1 = den2 = 0.0;
        std::for_each(sim.cbegin(), sim.cend(), [&](std::pair<std::string, double>const& item){
            num +=  itemBasedmatrix[item1][item.first] * itemBasedmatrix[item2][item.first];
            den1 += pow(itemBasedmatrix[item1][item.first], 2);
            den2 += pow(itemBasedmatrix[item2][item.first], 2);
        });
        if (den1 == 0 || den2 == 0) return double(0);
        auto result = num / (sqrt(den1) * sqrt(den2));
        return result;
    }

    double AdjustedCosine::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >&itemBasedmatrix,
        std::map<std::string, std::map<std::string, ItemPrediction> >&userBasedmatrix,
        const std::string& item1,
        const std::string& item2)
    {
        std::map<std::string, double> sim;
        for (auto &&item : itemBasedmatrix[item1]){
            if (itemBasedmatrix[item2].count(item.first) == 1) {
                sim.insert(std::pair<std::string, double>(item.first, 1));
            }
        }

        if (sim.size() == 0) return 0;
        double num, den1, den2;
        num = den1 = den2 = 0.0;
        std::for_each(sim.cbegin(), sim.cend(), [&](std::pair<std::string, double>const& item){
            auto avgUser = getUserAverageScore(userBasedmatrix, item.first);
            auto num1 = itemBasedmatrix[item1][item.first] - avgUser;
            auto num2 = itemBasedmatrix[item2][item.first] - avgUser;
            num +=  num1 * num2;
            den1 += pow(num1, 2);
            den2 += pow(num2, 2);
        });
        if (den1 == 0 || den2 == 0) return double(0);
        auto result = num / (sqrt(den1) * sqrt(den2));
        return result;
    }

    double CorrelationBased::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >&itemBasedMatrix,
        std::map<std::string, std::map<std::string, ItemPrediction> >&userBasedMatrix,
        const std::string& item1,
        const std::string& item2)
    {
        std::map<std::string, double> sim;
        for (auto &&user : itemBasedMatrix[item1]){
            if (itemBasedMatrix[item2].count(user.first) == 1) {
                sim.insert(std::pair<std::string, double>(user.first, 1));
            }
        }

        if (sim.size() == 0) return double(0);
        double num, den1, den2;
        num = den1 = den2 = 0.0;
        auto avgItem1 = getUserAverageScore(itemBasedMatrix, item1);
        auto avgItem2 = getUserAverageScore(itemBasedMatrix, item2);
        std::for_each(
            sim.cbegin(),
            sim.cend(),
            [&](std::pair<std::string, double>const& user){
                auto num1 = itemBasedMatrix[item1][user.first] - avgItem1;
                auto num2 = itemBasedMatrix[item2][user.first] - avgItem2;
                num +=  num1 * num2;
                den1 += pow(num1, 2);
                den2 += pow(num2, 2);
        });
        if (den1 == 0 || den2 == 0) return double(0);
        auto result = num / (sqrt(den1) * sqrt(den2));
        return result;
    }
}
