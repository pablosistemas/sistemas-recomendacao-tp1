#ifndef RATING_H
#define RATING_H

#include "../UserItemPrediction/UserItemPrediction.h"

#include <string>
#include <ctime>

class Rating : public UserItemPrediction {
    public:
    std::time_t tstamp;

    Rating(const Rating &);

    Rating();

    Rating(std::string, std::string, float, std::time_t);

    Rating operator=(const Rating &rating) {
        Rating newRating (rating);
        return newRating;
    }
};

#endif
