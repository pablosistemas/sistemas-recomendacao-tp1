#ifndef PREDICTORS_H
#define PREDICTORS_H

#include <map>

#include "../ItemPrediction/ItemPrediction.h"

namespace Predictors {

    struct SimpleRecommender {
        double operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, double> >&,
            const std::string&,
            const std::string&);
    };
}

#endif