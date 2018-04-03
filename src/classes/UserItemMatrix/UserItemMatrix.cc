#include "../ItemPrediction/ItemPrediction.cc"
#include "../BaseList/BaseList.h"
#include "./UserItemMatrix.h"

#include <algorithm>
#include <fstream>
#include <cmath>

double UserItemMatrix::pearsonCorrelation(std::string userId1, std::string userId2)
{
    std::map<std::string, int> ratingsInCommon;
    std::for_each(dRatings[userId1].cbegin(), dRatings[userId1].cend(),
        [&] (std::pair<std::string,ItemPrediction> item){
            auto iti = dRatings[userId2].find(item.first);
            if (iti != dRatings[userId2].end()) {
                ratingsInCommon[item.first] = 1;
            }
        });
    auto n = ratingsInCommon.size();
    if (n == 0) return 0;

    double sum1, sum2, sum1Sq, sum2Sq, pSum;
    sum1 = sum2 = sum1Sq = sum2Sq = pSum = 0;

    std::for_each(ratingsInCommon.cbegin(), ratingsInCommon.cend(), [&](std::pair<std::string, int> itm) {
        sum1 += dRatings[userId1][itm.first].prediction;
        sum2 += dRatings[userId2][itm.first].prediction;

        sum1Sq += pow(dRatings[userId1][itm.first].prediction, 2);
        sum2Sq += pow(dRatings[userId2][itm.first].prediction, 2);

        pSum += dRatings[userId1][itm.first].prediction * dRatings[userId2][itm.first].prediction;
    });

    auto num = pSum - (sum1 * sum2 / n);
    auto den = sqrt(sum1Sq - pow(sum1,2)/n) * (sum2Sq - pow(sum2,2)/n);
    if (den == 0) return double(0);
    return num/den;
}

void UserItemMatrix::setMatrixFromRatingList()
{
    std::vector<std::vector<Rating> >::iterator itm;
    std::vector<Rating>::iterator itr;

    userItemMatrix.resize(ratings.userIndex.size());

    for(itm = userItemMatrix.begin(); itm != userItemMatrix.end(); itm++)
    {
        (*itm).resize(ratings.itemIndex.size());
    }

    for(itr = ratings.ratings.begin(); itr != ratings.ratings.end(); itr++) {
        auto userId = ratings.getIndexOf(itr->userId);
        auto itemId = ratings.getIndexOf(itr->itemId);
        userItemMatrix[userId][itemId] = (*itr);
    }
}

void UserItemMatrix::predictionFromFile(std::string pathToFile)
{
    auto file = std::ifstream(pathToFile.c_str());
    std::string title, line;
    std::getline(file, title, '\n');
    while (file.good()){
        std::getline(file, line, '\n');
        auto userItemIds = BaseList::getUserIdFromString(line);
        
    }
}

void UserItemMatrix::predict(std::string userId, std::string itemId)
{
}

void UserItemMatrix::addLineToMap(std::string line)
{
    auto lineStream = std::stringstream(line);
    std::string userItemIds, prediction, timestamp;
    std::getline(lineStream, userItemIds, ',');
    std::getline(lineStream, prediction, ',');
    std::getline(lineStream, timestamp, ',');
    std::tuple<std::string, std::string> userItem = BaseList::getUserIdFromString(userItemIds);
    dRatings[std::get<0>(userItem)].insert( std::pair<std::string,ItemPrediction>(std::get<1>(userItem),
        *(new ItemPrediction(
            (double)atof(prediction.c_str()),
            (time_t) strtol (timestamp.c_str(), NULL, 10)
        ))
    ));
}

void UserItemMatrix::readRatingsAsMap(std::string pathToFile)
{
    auto file = std::ifstream(pathToFile.c_str());
    std::string title, line;
    std::getline(file, title, '\n');
    while(file.good()){
        std::getline(file, line, '\n');
        addLineToMap(line);
    }
}

std::vector<double> UserItemMatrix::topMatches(
    std::string person,
    std::function<double(std::string, std::string)> similarity)
{
    std::vector<double> scores;
    std::for_each(dRatings.begin(), dRatings.end(),
    [&](std::pair<std::string, std::map<std::string, ItemPrediction> > rating){
        if (rating.first != person) {
            scores.push_back(similarity(person, rating.first));
        }
    });

    std::sort(scores.begin(), scores.end(), 
    [] (double score1, double score2) { return score1 > score2; });
    return scores;
}

std::vector<double> UserItemMatrix::getRecommendations(
    std::string person,
    std::function<double(std::string, std::string)> similarity)
{

}

void UserItemMatrix::calculateSimilarItems()
{
    
}