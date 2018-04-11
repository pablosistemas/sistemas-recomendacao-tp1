#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include <cmath>

namespace Helpers {
    template <typename T>
    std::vector<T> slice(std::vector<T> &v, int m, int n) {
        auto first = v.begin() + m;
        auto last = v.begin() + n;
        std::vector<T> vec;
        for (auto it = first; it != last; it++) {
            vec.push_back(*it);
        }
        return vec;
    }

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
}

#endif