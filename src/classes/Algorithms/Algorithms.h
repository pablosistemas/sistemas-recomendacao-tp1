#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "../RatingList/RatingList.h"
#include "../ItemPrediction/ItemPrediction.h"
#include <map>

namespace Algorithms {
    struct ItemToItem {
        void operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, double> >&,
            RatingList &,
            int=-1, int=-1
        );
    };

    struct UserToUser {
        void operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, double> >&,
            RatingList &,
            int=-1, int=-1
        );
    };
}

#endif