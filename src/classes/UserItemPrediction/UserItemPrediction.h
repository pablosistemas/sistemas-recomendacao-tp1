#ifndef USER_ITEM_PREDICTION
#define USER_ITEM_PREDICTION

#include "../UserItemList/UserItemList.h"

struct UserItemPrediction : public UserItemList
{
    double prediction;
};

#endif
