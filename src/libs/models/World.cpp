#include "World.h"

void World::processJsonMap(std::map<std::string, signalr::value> worldMap) {
    if (worldMap.size() >= 2) {
        std::map <std::string, bool> sectionKeyMap;
        std::stringstream ss;
        for (const auto& [key, value] : worldMap) {
            if (value.is_string())
                ss << "[" << key << "]=" << value.as_string() << std::endl;
            if (key.compare("size") == 0) {
                sectionKeyMap.insert(std::make_pair("size", true));
            }
            if (key.compare("currentTick") == 0) {
                sectionKeyMap.insert(std::make_pair("currentTick", true));
            }
            //if (key.compare("populationTiers") == 0) {
            //    sectionKeyMap.insert(std::make_pair("populationTiers", true));
            //}
        }
        std::map<std::string, signalr::value> gameMap;
        // = worldMap.find("map")->second.as_map();
        if (worldMap.find("map")->second.is_map())
            gameMap = worldMap.find("map")->second.as_map();
        if (worldMap.find("map")->second.is_array())
            gameMap = worldMap.find("map")->second.as_array()[0].as_map();
        std::cout << "World::processJsonMap = " << std::endl
                  << ss.str() << std::endl;
        map.processJsonMap(gameMap);
    }
}


