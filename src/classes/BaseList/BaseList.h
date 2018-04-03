#ifndef BASE_LIST_H
#define BASE_LIST_H

#include <string>
#include <tuple>
#include <sstream>

struct BaseList {
    #pragma region STATIC_METHODS
    static std::tuple<std::string, std::string> getUserIdFromString(std::string userItem)
    {
        auto userItemStream = std::stringstream(userItem);
        std::string userId, itemId;
        std::getline(userItemStream, userId, ':');
        std::getline(userItemStream, itemId, '\n');
        return std::make_tuple(userId, itemId);
    }
    #pragma endregion
};

#endif