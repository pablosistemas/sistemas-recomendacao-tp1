#ifndef SIMILARITY_H
#define SIMILARITY_H

#include <iostream>
#include <map>
#include "../ItemPrediction/ItemPrediction.h"

namespace Similarity {

    struct BaseSimilarity {
        virtual double operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            const std::string&,
            const std::string&) = 0;
    };

    struct Pearson : public BaseSimilarity { 
        double operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            const std::string&,
            const std::string&);
    };

    struct CorrelationBased : public BaseSimilarity { 
        double operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            const std::string&,
            const std::string&);
    };


    struct Distance : public BaseSimilarity { 
        double operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            const std::string&,
            const std::string&);
    };

    struct Cosine : public BaseSimilarity { 
        double operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            const std::string&,
            const std::string&);
    };

    struct AdjustedCosine : public BaseSimilarity { 
        double operator()(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            const std::string&,
            const std::string&);
    };
}

#endif