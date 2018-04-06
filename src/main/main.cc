#include <iostream>
#include <functional>

#include "../classes/UserItemMatrix/UserItemMatrix.cc"
#include "../classes/Similarity/Similarity.cc"
#include "../classes/Predictors/Predictors.cc"
#include "../classes/TopMatches/TopMatches.cc"

using namespace Similarity;
using namespace Predictors;
using namespace Recommender;

int main(int argc, char **argv) {
    UserItemMatrix matrix;
    // matrix.ratings.readRatings(std::string("data/ratings100.csv"));
    matrix.setMatrixFromRatingList();
    matrix.readRatingsAsMap(std::string("data/ratingsex.csv"));
    matrix.createItemBasedMatrixFromUserBasedMatrix();

    auto nome1 = std::string("Lisa Rose");
    auto nome2 = std::string("Gene Seymour");
    auto res = Pearson()(matrix.dRatings, nome1, nome2);
    auto res1 = Distance()(matrix.dRatings, nome1, nome2);

    auto top = TopMatches()(matrix.dRatings,"Toby", Pearson());

    auto topI = TopMatches()(matrix.itemBasedMatrix,"Superman Returns", Pearson());

    auto similar = matrix.calculateSimilarItems(matrix.itemBasedMatrix, Pearson());
    auto rec = matrix.getRecommendations(matrix.dRatings, "Toby", Distance());
    auto recomm = SimpleRecommender()(
        matrix.dRatings,
        similar,
        "Toby",
        "The Night Listener"
    );
}
