#ifndef TOP_MATCHES_H
#define TOP_MATCHES_H

#include "../ItemPrediction/ItemPrediction.h"
#include "../Helpers/Helpers.h"
#include <functional>
#include <vector>
#include <map>

namespace Recommender {
    struct TopMatches {
        std::vector<std::pair<std::string, double> > operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::string,
            std::function<double(
                std::map<std::string, std::map<std::string, ItemPrediction> >&,
                std::map<std::string, std::map<std::string, ItemPrediction> >&,
                const std::string&,
                const std::string&)>,
            int=-1, int=-1, bool=false
        );
    };
}

#endif