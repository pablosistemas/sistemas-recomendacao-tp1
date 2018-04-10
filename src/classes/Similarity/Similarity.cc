#include "./Similarity.h"
#include <algorithm>
#include <cmath>

namespace Similarity{

    double Pearson::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >& customBasedMatrix,
        const std::string& userId1,
        const std::string& userId2)
    {
        std::map<std::string, int> ratingsInCommon;
        std::for_each(customBasedMatrix[userId1].cbegin(), customBasedMatrix[userId1].cend(),
            [&] (std::pair<std::string,ItemPrediction> item){
                auto iti = customBasedMatrix[userId2].find(item.first);
                if (iti != customBasedMatrix[userId2].end()) {
                    ratingsInCommon[item.first] = 1;
                }
            });
        auto n = ratingsInCommon.size();
        if (n == 0) return 0;

        double sum1, sum2, sum1Sq, sum2Sq, pSum;
        sum1 = sum2 = sum1Sq = sum2Sq = pSum = 0;

        std::for_each(ratingsInCommon.cbegin(), ratingsInCommon.cend(), [&](std::pair<std::string, int> itm) {
            sum1 += customBasedMatrix[userId1][itm.first].prediction;
            sum2 += customBasedMatrix[userId2][itm.first].prediction;

            sum1Sq += pow(customBasedMatrix[userId1][itm.first].prediction, 2);
            sum2Sq += pow(customBasedMatrix[userId2][itm.first].prediction, 2);

            pSum += customBasedMatrix[userId1][itm.first].prediction * customBasedMatrix[userId2][itm.first].prediction;
        });

        auto num = pSum - (sum1 * sum2 / n);
        auto den = sqrt((sum1Sq - pow(sum1,2)/n) * (sum2Sq - pow(sum2,2)/n));
        if (den == 0) return double(0);
        std::cout << pSum << " " << sum1 << " " << sum2 << " " << den << " " << n <<"\n";
        std::cout << "Pearson (" << userId1 << ", " << userId2 << ") = " << num/den << "\n\n";
        return num/den;
    }

    double Distance::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >&userOrItemMatrix,
        const std::string& userOrItem1,
        const std::string& userOrItem2)
    {
        std::map<std::string, double> sim;
        for (auto &&item : userOrItemMatrix[userOrItem1]){
            if (userOrItemMatrix[userOrItem2].count(item.first) == 1) {
                sim.insert(*new std::pair<std::string, double>(item.first, 1));
            }
        }

        if (sim.size() == 0) return 0;
        double sum = 0.0;
        std::for_each(sim.cbegin(), sim.cend(), [&](std::pair<std::string, double>const& item){
            sum += pow(userOrItemMatrix[userOrItem1][item.first] - userOrItemMatrix[userOrItem2][item.first], 2);
        });
        auto sum1 = 1.0/(1.0 + sqrt(sum));
        return sum1;
    }

    double Cosine::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >&userOrItemMatrix,
        const std::string& userOrItem1,
        const std::string& userOrItem2)
    {
        std::map<std::string, double> sim;
        for (auto &&item : userOrItemMatrix[userOrItem1]){
            if (userOrItemMatrix[userOrItem2].count(item.first) == 1) {
                sim.insert(*new std::pair<std::string, double>(item.first, 1));
            }
        }

        if (sim.size() == 0) return 0;
        double num, den1, den2;
        num = den1 = den2 = 0.0;
        std::for_each(sim.cbegin(), sim.cend(), [&](std::pair<std::string, double>const& item){
            num += userOrItemMatrix[userOrItem1][item.first] * userOrItemMatrix[userOrItem2][item.first];
            den1 += pow(userOrItemMatrix[userOrItem1][item.first], 2);
            den2 += pow(userOrItemMatrix[userOrItem2][item.first], 2);
        });
        auto result = num / (sqrt(den1) * sqrt(den2));
        return result;
    }
}

