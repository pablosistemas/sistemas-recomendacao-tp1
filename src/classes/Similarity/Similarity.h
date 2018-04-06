#ifndef SIMILARITY_H
#define SIMILARITY_H

#include <iostream>
#include <map>
#include "../ItemPrediction/ItemPrediction.h"

namespace Similarity {
    struct Pearson {
        double operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            const std::string&,
            const std::string&);
    };

    struct Distance {
        double operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            const std::string&,
            const std::string&);
    };
}

#endif