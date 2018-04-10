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

    double operator*(const ItemPrediction& b) {
            return prediction * b.prediction;
    }

    explicit operator double () { return prediction; }
    operator double () const { return prediction; }
};

#endif
