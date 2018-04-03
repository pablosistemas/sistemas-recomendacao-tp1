#include <iostream>
#include <functional>

#include "../classes/UserItemMatrix/UserItemMatrix.cc"

int main(int argc, char **argv) {
    UserItemMatrix matrix;
    // matrix.ratings.readRatings(std::string("data/ratings100.csv"));
    matrix.setMatrixFromRatingList();
    matrix.readRatingsAsMap(std::string("data/ratings100.csv"));
    auto fn = std::bind(&UserItemMatrix::pearsonCorrelation, matrix);
    matrix.topMatches("u0006099", fn);
    // matrix.pearsonCorrelation();
}
