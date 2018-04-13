#include "TopMatches.h"
#include "../Helpers/Helpers.h"

#include <algorithm>
#include <random>

namespace Recommender {
    std::vector<std::pair<std::string, double> > TopMatches::operator()(
        std::map<std::string, std::map<std::string, ItemPrediction> >& customBasedMatrix,
        std::string person,
        std::function<double(
                std::map<std::string, std::map<std::string, ItemPrediction> >&,
                const std::string&,
                const std::string&)> similarity,
        int kNeighbors, int pPairs, bool randomize)
    {
        int n = 0;
        std::map<std::string, double> scores;
        if (!randomize || pPairs > (int)(customBasedMatrix.size() - 1) || pPairs == -1) {
            std::all_of(customBasedMatrix.begin(), customBasedMatrix.end(),
            [&](std::pair<std::string, std::map<std::string, ItemPrediction> > rating){
                if (n >= pPairs && pPairs != -1) return false;
                if (rating.first != person) {
                    auto itemSimilarity = similarity(customBasedMatrix, person, rating.first);
                    if (itemSimilarity != 0.0) {
                        scores[rating.first] = itemSimilarity;
                    }
                    n++; // in cold-start it is possible to exist just few or no similarities
                }
                return true;
            });
        } else {
            std::mt19937 rng;
            rng.seed(std::random_device()());
            std::uniform_int_distribution<std::mt19937::result_type> dist(0, customBasedMatrix.size() - 1);
            int nPairs = pPairs > 0 && pPairs < (int)customBasedMatrix.size() ? pPairs : customBasedMatrix.size();
            for (; n < nPairs;) {
                auto it = std::next(customBasedMatrix.begin(), dist(rng));
                if (it->first != person && scores.count(it->first) == 0) {
                    auto itemSimilarity = similarity(customBasedMatrix, person, it->first);
                    if (itemSimilarity != 0.0) {
                        scores[it->first] = itemSimilarity;
                    }
                    n++;
                }
            }
        }

        std::vector<std::pair<std::string, double> > pairs;
        for (auto itr = scores.begin(); itr != scores.end(); ++itr)
            pairs.push_back(*itr);

        std::sort(pairs.begin(), pairs.end(),
        [](std::pair<std::string, double> &a, std::pair<std::string, double> &b)
        {
            return a.second > b.second;
        });

        if (kNeighbors == -1 || kNeighbors > (int)pairs.size())
            return pairs;
        return Helpers::slice<std::pair<std::string, double> >(pairs, 0, kNeighbors);
    }
}