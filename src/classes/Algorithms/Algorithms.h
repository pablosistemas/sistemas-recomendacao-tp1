#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "../ItemPrediction/ItemPrediction.h"
#include "../RatingList/RatingList.h"
#include <map>

namespace Algorithms {
    struct ItemToItem {
        void operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, double> >&,
            RatingList &,
            double*, int*, int=-1, int=-1
        );
    };

    struct UserToUser {
        void operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, double> >&,
            RatingList &
        );
    };

    struct Hybrid {
        void operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, double> >&,
            std::map<std::string, std::map<std::string, double> >&,
            RatingList &,
            double*, int*, int=-1, int=-1
        );
    };
}

#endif