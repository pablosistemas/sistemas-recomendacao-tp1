#include "../ItemPrediction/ItemPrediction.cc"
#include "../TopMatches/TopMatches.h"
#include "../BaseList/BaseList.h"
#include "./UserItemMatrix.h"
#include "../FileManager/FileManager.h"

#include <algorithm>
#include <fstream>
#include <cmath>

using namespace Recommender;

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

void UserItemMatrix::readRatingsAsMap(std::string pathToFile)
{
    FileManager::read<std::map<std::string, std::map<std::string, ItemPrediction> >>(pathToFile, dRatings);
}

template<typename A, typename B>
std::pair<B,A> flipPair (const std::pair<A,B> &p) {
    return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::map<B,A> flipMap (const std::map<A,B> &src) {
    std::map<B,A> flippedMap;
    std::transform(src.begin(), src.end(), std::inserter(flippedMap, flippedMap.begin()), flipPair<A,B>);
    return flippedMap;
}

std::vector<std::pair<std::string, double> > UserItemMatrix::getRecommendations(
    std::map<std::string, std::map<std::string, ItemPrediction> >& userItemMatrix,
    std::string userOrItem,
    std::function<double(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            const std::string&,
            const std::string&)> similarity)
{
    std::map<std::string, double> totals, simSums;
    for (auto otherUserOrItem : userItemMatrix) {
        if (otherUserOrItem.first == userOrItem) continue;
        auto sim = similarity(userItemMatrix, userOrItem, otherUserOrItem.first);
        if (sim <= 0) continue;
        for (auto && itemRating : userItemMatrix[otherUserOrItem.first]) {
            if (userItemMatrix[userOrItem].count(itemRating.first) == 1 &&
                userItemMatrix[userOrItem][itemRating.first].prediction != 0) continue;
            totals[itemRating.first] += userItemMatrix[otherUserOrItem.first][itemRating.first].prediction * sim;
            simSums[itemRating.first] += sim;
        }
    }

    std::vector<std::pair<std::string, double> > rankings;
    for (auto &&item : totals) {
        rankings.push_back(*new std::pair<std::string, double>(item.first, item.second/simSums[item.first]));
    }

    std::sort(rankings.begin(), rankings.end(), 
    [&] (std::pair<std::string, double>& a, std::pair<std::string, double>& b){
        return a.second > b.second;
    });
    return rankings;
}

std::map<std::string, std::map<std::string, double> > UserItemMatrix::calculateSimilarItems(
    std::map<std::string, std::map<std::string, ItemPrediction> >& userOrItemBasedMatrix,
    std::function<double(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            const std::string&,
            const std::string&)> similarity,
    int K, int P, bool randomize)
{
    std::map<std::string, std::map<std::string, double> > scores;
    std::map<std::string, std::vector<std::pair<std::string, double> > > scoresRanked;
    for(auto itm = userOrItemBasedMatrix.cbegin(); itm != userOrItemBasedMatrix.cend(); itm++)
    {
        auto scoresItem = TopMatches()(userOrItemBasedMatrix, itm->first, similarity, K, P, randomize);
        std::for_each(scoresItem.cbegin(), scoresItem.cend(),
        [&](std::pair<std::string, double> const &pair) {
            scores[itm->first].insert(pair);
            scoresRanked[itm->first].push_back(pair);
        });
    }
    // std::for_each(scoresRanked.cbegin(), scoresRanked.cend(),
    // [&] (std::pair<std::string, std::vector<std::pair<std::string, double> > > similars) {
    //     std::sort(similars.second.begin(), similars.second.end(), 
    //     [&](std::pair<std::string, double> a, std::pair<std::string, double> b) {
    //         return a.second > b.second;
    //     });
    // });
    return scores;
}

void UserItemMatrix::createItemBasedMatrixFromUserBasedMatrix()
{
    for(auto itm = dRatings.cbegin(); itm != dRatings.cend(); itm++){
        std::for_each(itm->second.cbegin(), itm->second.cend(), [&](std::pair<std::string, ItemPrediction> pair){
            itemBasedMatrix[pair.first][itm->first] = pair.second;
        });
    }
}
