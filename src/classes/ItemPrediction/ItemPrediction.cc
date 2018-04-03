#include "ItemPrediction.h"

ItemPrediction::ItemPrediction() {}

ItemPrediction::ItemPrediction(double prediction, time_t tstamp)
{
    this->prediction = prediction;
    this->tstamp = tstamp;
}
