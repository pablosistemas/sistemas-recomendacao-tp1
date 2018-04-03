#include "Rating.h"

Rating::Rating() {}

Rating::Rating (const Rating &rating)
{
    userId = rating.userId;
    itemId = rating.itemId;
    prediction = rating.prediction;
    tstamp = rating.tstamp;
}

Rating::Rating (
    std::string usrId,
    std::string itId,
    float predict,
    std::time_t tstamp
)
{
    this->userId = usrId;
    this->itemId = itId;
    this->prediction = predict;
    this->tstamp = tstamp;
}
