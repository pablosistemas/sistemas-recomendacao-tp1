#ifndef HELPERS_H
#define HELPERS_H

#include <vector>

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
}

#endif