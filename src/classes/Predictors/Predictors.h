#ifndef PREDICTORS_H
#define PREDICTORS_H

#include "../ItemPrediction/ItemPrediction.h"
#include <vector>
#include <map>

namespace Predictors {

    struct SimpleRecommender {
        double operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, double> >&,
            const std::string&,
            const std::string&);
    };

    struct NeighborPrediction {
        double operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::vector<std::pair<std::string, double> >&,
            const std::string&,
            const std::string&);

    };
}

#endif