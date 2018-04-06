#ifndef TOP_MATCHES_H
#define TOP_MATCHES_H

#include <functional>
#include <vector>
#include <map>
#include "../ItemPrediction/ItemPrediction.h"

namespace Recommender {
    struct TopMatches {
        std::vector<std::pair<std::string, double> > operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::string,
            std::function<double(
                std::map<std::string, std::map<std::string, ItemPrediction> >&,
                const std::string&,
                const std::string&)>
            );
    };
}

#endif