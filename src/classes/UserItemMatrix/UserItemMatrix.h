#ifndef USER_ITEM_MATRIX_H
#define USER_ITEM_MATRIX_H

#include "../ItemPrediction/ItemPrediction.h"
#include "../RatingList/RatingList.h"
#include "../Rating/Rating.h"

#include <functional>

struct UserItemMatrix {
    std::map<std::string, std::map<std::string, ItemPrediction> > userBasedMatrix;
    std::map<std::string, std::map<std::string, ItemPrediction> > itemBasedMatrix;
    std::vector<std::vector<Rating> > userItemMatrix;
    RatingList ratings;

    void setMatrixFromRatingList();

    void readUserRatingsAsMap(std::string const&);

    std::vector<std::pair<std::string, double> > getRecommendations(
        std::map<std::string, std::map<std::string, ItemPrediction> >& userItemMatrix,
        std::string,
        std::function<double(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            const std::string&,
            const std::string&)>);

    std::map<std::string, std::map<std::string, double> > calculateSimilarItems(
        std::map<std::string, std::map<std::string, ItemPrediction> >&,
        std::map<std::string, std::map<std::string, ItemPrediction> >&,
        std::function<double(
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            std::map<std::string, std::map<std::string, ItemPrediction> >&,
            const std::string&,
            const std::string&)>,
        int=-1, int =-1, bool=false
    );

    void createItemBasedMatrixFromUserBasedMatrix();

    private:
    void addLineToMap(std::string);
};

#endif
