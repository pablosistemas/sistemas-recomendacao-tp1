#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include <sstream>
#include <tuple>

#include "../ItemPrediction/ItemPrediction.h"
#include "../BaseList/BaseList.h"

struct FileManager {
    template<typename A>
    static void read (const std::string &fileName, A& container) {
        auto file = std::ifstream(fileName.c_str());
        std::string title, line;
        std::getline(file, title, '\n');
        while(file.good()){
            std::getline(file, line, '\n');
            if (line != "") {
                auto rating = parseLine(line);
                container[std::get<0>(rating)].insert( 
                    std::pair<std::string,ItemPrediction>(
                        std::get<1>(rating),
                        *(new ItemPrediction(
                            std::get<2>(rating),
                            std::get<3>(rating))
                        ))
                ); 
            }
        }
        file.close();
    }

    static std::tuple<std::string, std::string, double, time_t> parseLine(const std::string& line)
    {
        auto lineStream = std::stringstream(line);
        std::string userItemIds, prediction, timestamp;
        std::getline(lineStream, userItemIds, ',');
        std::getline(lineStream, prediction, ',');
        std::getline(lineStream, timestamp, ',');
        std::tuple<std::string, std::string> userItem = BaseList::getUserIdFromString(userItemIds);
        return std::make_tuple (
            std::get<0>(userItem),
            std::get<1>(userItem),
            (double)atof(prediction.c_str()),
            (time_t) strtol (timestamp.c_str(), NULL, 10)
        );
    }
};

#endif