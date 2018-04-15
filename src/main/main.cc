#include <functional>
#include <iostream>
#include <vector>
#include <chrono>
#include <tuple>

#include "../classes/UserItemMatrix/UserItemMatrix.h"
#include "../classes/Similarity/Similarity.h"
#include "../classes/Algorithms/Algorithms.h"

using namespace Algorithms;
using namespace Similarity;

int main(int argc, char **argv) {
    if (argc < 2) return -1;

    UserItemMatrix matrix;
    matrix.readUserRatingsAsMap(std::string(argv[1]));
    matrix.createItemBasedMatrixFromUserBasedMatrix();

    std::vector<std::tuple<std::string, std::string, double>> targetScores;
    RatingList targets;
    targets.readRatings(argv[2]);

    auto K = 40;
    auto P = 60;

    auto similarItems = matrix.calculateSimilarItems(
        matrix.itemBasedMatrix,
        matrix.userBasedMatrix,
        Cosine(),
        K, P, true);

    ItemToItem()(
        matrix.itemBasedMatrix,
        matrix.userBasedMatrix,
        similarItems,
        targets, K, P);

    // auto K = 20;
    // auto P = 30;

    // UserToUser()(
    //     matrix.userBasedMatrix, 
    //     matrix.itemBasedMatrix,
    //     targets,
    //     K, P, true
    // );

    return 0;
}
