#ifndef RATING_LIST_H
#define RATING_LIST_H

#include "../Rating/Rating.h"

#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>
#include <map>

struct RatingList {
    std::map<std::string, unsigned long> userIndex, itemIndex;
    std::vector<Rating> ratings;
    unsigned long countIdx;
    
    public:
    RatingList();
    unsigned long getIndexOf(std::string, bool user=true);
    void readRatings(std::string pathToFile);
    void addLineToList(std::string line);
};

#endif
