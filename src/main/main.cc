#include <iostream>
#include <functional>

#include "../classes/UserItemMatrix/UserItemMatrix.cc"

int main(int argc, char **argv) {
    UserItemMatrix matrix;
    // matrix.ratings.readRatings(std::string("data/ratings100.csv"));
    matrix.setMatrixFromRatingList();
    matrix.readRatingsAsMap(std::string("data/ratingsex.csv"));
    matrix.createItemBasedMatrixFromUserBasedMatrix();
    auto res = matrix.pearsonCorrelation(matrix.dRatings, "Lisa Rose", "Gene Seymour");
    auto top = matrix.topMatches(matrix.dRatings ,"Toby", true);
    auto similar = matrix.calculateSimilarItems();
    // matrix.pearsonCorrelation();
}
