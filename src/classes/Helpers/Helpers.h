#ifndef HELPERS_H
#define HELPERS_H

#include "../ItemPrediction/ItemPrediction.h"
#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include <cmath>
#include <map>

namespace Helpers {
    template <typename T>
    std::vector<T> slice(std::vector<T> &v, int m, int n)
    {
        auto first = v.begin() + m;
        auto last = v.begin() + n;
        std::vector<T> vec;
        for (auto it = first; it != last; it++) {
            vec.push_back(*it);
        }
        return vec;
    }

    template<typename A, typename B>
    std::pair<B,A> flipPair (const std::pair<A,B> &p) {
        return std::pair<B,A>(p.second, p.first);
    }

    template<typename A, typename B>
    std::map<B,A> flipMap (const std::map<A,B> &src) {
        std::map<B,A> flippedMap;
        std::transform(src.begin(), src.end(), std::inserter(flippedMap, flippedMap.begin()), flipPair<A,B>);
        return flippedMap;
    }

    double getUserAverageScore(
        std::map<std::string, std::map<std::string, ItemPrediction> >&,
        std::string);

    struct TimestampManip {
        static int differenceInYears(time_t *tstamp1, time_t *tstamp2)
        {
            auto tstampStruct1 = localtime(tstamp1);
            auto tstampStruct2 = localtime(tstamp2);
            return std::abs(tstampStruct1->tm_year - tstampStruct2->tm_year);
        }

        static int getMovieDecade(time_t *tstamp) {
            auto tstampStruct = localtime(tstamp);
            auto decade = (tstampStruct->tm_year >> 4) << 4;
            return decade;
        }
    };

    template<typename T>
    std::function <void(T *)> destroyPtr = [] (T *p) {
       delete p;
    };
}

#endif