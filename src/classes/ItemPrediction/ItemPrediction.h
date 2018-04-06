#ifndef ITEM_PREDICTION_H
#define ITEM_PREDICTION_H

#include <string>
#include <ctime>

struct ItemPrediction {
    double prediction;
    time_t tstamp;

    ItemPrediction();
    ItemPrediction(double, time_t);

    double operator-(const ItemPrediction& b) {
            return prediction - b.prediction;
   }
};

#endif
