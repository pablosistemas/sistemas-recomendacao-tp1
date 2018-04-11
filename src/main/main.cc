#include <functional>
#include <iostream>
#include <vector>
#include <chrono>
#include <tuple>

#include "../classes/UserItemMatrix/UserItemMatrix.cc"
#include "../classes/Similarity/Similarity.cc"
#include "../classes/Predictors/Predictors.cc"
#include "../classes/TopMatches/TopMatches.cc"
#include "../classes/Algorithms/Algorithms.cc"
#include "../classes/Helpers/Helpers.cc"

using namespace Recommender;
using namespace Algorithms;
using namespace Predictors;
using namespace Similarity;
using namespace Helpers;

int main(int argc, char **argv) {

    if (argc < 2) return -1;

    UserItemMatrix matrix;
    matrix.readRatingsAsMap(std::string(argv[1]));
    matrix.createItemBasedMatrixFromUserBasedMatrix();

    std::vector<std::tuple<std::string, std::string, double>> targetScores;
    RatingList targets;
    targets.readRatings(argv[2]);

    // TimestampManip::differenceInYears(&matrix.itemBasedMatrix["i0444778"]["u0026502"].tstamp);
    auto K = 40;
    auto P = 100;

    auto start = std::chrono::high_resolution_clock::now();
    auto similar = matrix.calculateSimilarItems(matrix.itemBasedMatrix, Cosine(), P, K, true);
    // auto similar = matrix.calculateSimilarItems(matrix.dRatings, Pearson(), K, P, true);
    auto stop = std::chrono::high_resolution_clock::now();
    auto timeSpent = std::chrono::duration_cast <std::chrono::seconds> ( stop - start ).count();
    std::cout << "Time spent: " << timeSpent << std::endl;
    ItemToItem()(matrix.itemBasedMatrix, matrix.dRatings, similar, targets, K, P);
    // UserToUser()(matrix.dRatings, similar, targets, K, P);

    // auto similar = matrix.calculateSimilarItems(matrix.dRatings, Pearson());
    // std::cout << "UserId:ItemId,Prediction" << std::endl;
    // for (auto it = targets.ratings.cbegin(); it != targets.ratings.cend(); it++){
    //     auto top = TopMatches()(matrix.dRatings, it->userId, Pearson(), K, P);
    //     auto predict = NeighborPrediction()(matrix.dRatings, top, it->userId, it->itemId); 
        /*auto result = std::make_tuple(
            it->userId,
            it->itemId,
            SimpleRecommender()(
                matrix.dRatings, 
                similar,
                it->userId,
                it->itemId
            ));
        targetScores.push_back(result);
        std::cout << it->userId << ":" << it->itemId << "," << std::get<2>(result) << std::endl;
        */
        // std::cout << "Result" << std::endl;
        // std::cout << it->userId << ":" << it->itemId << "," << predict << std::endl;
    // }

    return 0;
}


    /*UserItemMatrix matrix;
    // matrix.ratings.readRatings(std::string("data/ratings100.csv"));
    matrix.setMatrixFromRatingList();
    matrix.readRatingsAsMap(std::string("data/ratingsex.csv"));
    matrix.createItemBasedMatrixFromUserBasedMatrix();

    auto nome1 = std::string("Lisa Rose");
    auto nome2 = std::string("Gene Seymour");
    auto res = Pearson()(matrix.dRatings, nome1, nome2);
    auto res1 = Distance()(matrix.dRatings, nome1, nome2);

    auto top = TopMatches()(matrix.dRatings,"Toby", Pearson());
    auto top = TopMatches()(matrix.dRatings,"Toby", Pearson());
    auto topI = TopMatches()(matrix.itemBasedMatrix,"Superman Returns", Pearson());
    auto topI = TopMatches()(matrix.itemBasedMatrix,"Superman Returns", Pearson());

    auto similar = matrix.calculateSimilarItems(matrix.itemBasedMatrix, Pearson());
    auto rec = matrix.getRecommendations(matrix.dRatings, "Toby", Distance());
    auto recomm = SimpleRecommender()(
        matrix.dRatings,
        similar,
        "Toby",
        "The Night Listener"
    );

    nome1 = std::string("Just My Luck");
    nome2 = std::string("The Night Listener");
    auto cosine = Cosine()(matrix.itemBasedMatrix, nome1, nome2);*/
