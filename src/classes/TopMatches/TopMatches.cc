#include "TopMatches.h"
#include <algorithm>

namespace Recommender {
    std::vector<std::pair<std::string, double> > TopMatches::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >& customBasedMatrix,
        std::string person,
        std::function<double(
                std::map<std::string, std::map<std::string, ItemPrediction> >&,
                const std::string&,
                const std::string&)> similarity
        )
    {
        std::map<std::string, double> scores;
        std::for_each(customBasedMatrix.begin(), customBasedMatrix.end(),
        [&](std::pair<std::string, std::map<std::string, ItemPrediction> > rating){
            if (rating.first != person) {
                scores[rating.first] = similarity(customBasedMatrix, person, rating.first);
            }
        });

        std::vector<std::pair<std::string, double> > pairs;
        for (auto itr = scores.begin(); itr != scores.end(); ++itr)
            pairs.push_back(*itr);

        std::sort(pairs.begin(), pairs.end(),
        [] (std::pair<std::string, double> &a, std::pair<std::string, double> &b)
        {
            return a.second >= b.second;
        });

        return pairs;
    }
}