#ifndef USER_ITEM_MATRIX_H
#define USER_ITEM_MATRIX_H

#include "../Rating/Rating.h"
#include "../RatingList/RatingList.h"
#include "../ItemPrediction/ItemPrediction.h"

#include <functional>

struct UserItemMatrix {
    std::map<std::string, std::map<std::string, ItemPrediction> > dRatings;
    std::vector<std::vector<Rating> > userItemMatrix;
    RatingList ratings;

    double pearsonCorrelation(std::string, std::string);
    void setMatrixFromRatingList();

    void predict(std::string, std::string);
    void predictionFromFile(std::string);

    void readRatingsAsMap(std::string);

    std::vector<double> topMatches(std::string, std::function<double(std::string, std::string)>);
    std::vector<double> getRecommendations(std::string, std::function<double(std::string, std::string)>);
    void calculateSimilarItems();

    private:
    void addLineToMap(std::string);
};

#endif