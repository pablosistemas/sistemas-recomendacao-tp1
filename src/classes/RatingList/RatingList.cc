#include "../BaseList/BaseList.h"
#include "RatingList.h"

#include <fstream>
#include <sstream>
#include <tuple>

RatingList::RatingList() {
    countIdx = 0;
}

void RatingList::readRatings(std::string pathToFile)
{
    auto file = std::ifstream(pathToFile.c_str());
    std::string title, line;
    std::getline(file, title, '\n');
    while(file.good()){
        std::getline(file, line, '\n');
        addLineToList(line);
    }
}

void RatingList::addLineToList(std::string line)
{
    auto lineStream = std::stringstream(line);
    std::string userItemIds, prediction, timestamp;
    std::getline(lineStream, userItemIds, ',');
    std::getline(lineStream, prediction, ',');
    std::getline(lineStream, timestamp, ',');
    std::tuple<std::string, std::string> userItem = BaseList::getUserIdFromString(userItemIds);
    ratings.push_back(
        Rating(
            std::get<0>(userItem),
            std::get<1>(userItem),
            (float)atof(prediction.c_str()),
            (time_t) strtol (timestamp.c_str(), NULL, 10)
        )
    );
    getIndexOf(std::get<0>(userItem));
    getIndexOf(std::get<1>(userItem), false);
}

unsigned long RatingList::getIndexOf(std::string itemName, bool user)
{
    if (user) {
        if (userIndex.count(itemName) == 0) {
            userIndex[itemName] = countIdx++;
        }
        return userIndex[itemName];
    } else {
        if (itemIndex.count(itemName) == 0) {
            itemIndex[itemName] = countIdx++;
        }
        return itemIndex[itemName];
    }
}
