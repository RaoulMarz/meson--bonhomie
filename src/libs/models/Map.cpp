#include "Map.h"

void Map::processJsonMap(std::map<std::string, signalr::value> gameMap)
{
    std::string exceptionMarker;
    try
    {
        if (gameMap.size() >= 2)
        {
            std::map<std::string, bool> sectionKeyMap;
            std::stringstream ss;
            for (const auto &[key, value] : gameMap)
            {
                // ss << "[" << key << "]=";
                // ss << SignalRHelper::signalr_value_tostring(value, true, false);
                if (key.compare("scoutTowers") == 0)
                {
                    sectionKeyMap.insert(std::make_pair("scoutTowers", true));
                }
                if (key.compare("nodes") == 0)
                {
                    sectionKeyMap.insert(std::make_pair("nodes", true));
                }
                if (key.compare("availableNodes") == 0)
                {
                    sectionKeyMap.insert(std::make_pair("availableNodes", true));
                }
            }
            exceptionMarker = "find section keys";
            if (sectionKeyMap.find("scoutTowers") != sectionKeyMap.end())
            {
                /*
                if (gameMap.find("scoutTowers")->second.is_map() || gameMap.find("scoutTowers")->second.is_array())
                {
                    if (gameMap.find("scoutTowers")->second.is_map())
                        mapScoutTowers = gameMap.find("scoutTowers")->second.as_map();
                    if (gameMap.find("scoutTowers")->second.is_array() && (gameMap.find("scoutTowers")->second.as_array().size() > 0))
                        mapScoutTowers = gameMap.find("scoutTowers")->second.as_array()[0].as_map();

                    std::cout << "[section = scoutTowers]"
                              << " , content map size = " << mapScoutTowers.size() << std::endl;
                }
                */
               if (gameMap.find("scoutTowers")->second.is_array())
                {
                    vectorScoutTowers = gameMap.find("scoutTowers")->second.as_array();
                    std::cout << "[section = scoutTowers]"
                              << " , content map size = " << vectorScoutTowers.size() << std::endl;
                }
            }
            exceptionMarker = "extract vectorScoutTowers";
            if (sectionKeyMap.find("nodes") != sectionKeyMap.end())
            {
                if (gameMap.find("nodes")->second.is_array())
                {
                    vectorNodes = gameMap.find("nodes")->second.as_array();
                    std::cout << "[section = nodes]"
                              << " , content map size = " << vectorNodes.size() << std::endl;
                }
            }
            exceptionMarker = "extract vectorNodes";
            if (sectionKeyMap.find("availableNodes") != sectionKeyMap.end())
            {
                if (gameMap.find("availableNodes")->second.is_array())
                {
                    vectorAvailableNodes = gameMap.find("availableNodes")->second.as_array();
                    std::cout << "[section = availableNodes]"
                              << " , content map size = " << vectorAvailableNodes.size() << std::endl;
                }
            }
            exceptionMarker = "extract vectorAvailableNodes";
            std::cout << "Map::processJsonMap = " << std::endl
                      << ss.str() << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Map::processJsonMap :: exception: " << e.what() << " :: marker = " << exceptionMarker << std::endl;
    }
}

std::optional<std::vector<ScoutTower>> Map::getScoutTowers()
{
    std::optional<std::vector<ScoutTower>> result = std::nullopt;
    if (vectorScoutTowers.size() > 0)
    {
        std::optional<std::vector<ScoutTower>> result = std::make_optional<std::vector<ScoutTower>>(std::vector<ScoutTower>());
        for (signalr::value xTower : vectorScoutTowers)
        {
            // ss << "[" << key << "]=" << signalr_value_tostring(value, iterateMap, iterateArray) << std::endl;
            // result->push_back(xTower);
        }
        // result = std::make_optional<std::vector<ScoutTower>>(3.0, 4.0);
    }
    return result;
}

std::optional<std::vector<Node>> Map::getNodes()
{
    std::optional<std::vector<Node>> result = std::nullopt;
    if (vectorNodes.size() > 0)
    {
        std::optional<std::vector<Node>> result = std::make_optional<std::vector<Node>>(std::vector<Node>());
        for (signalr::value xNode : vectorNodes)
        {

        }
        // result = std::make_optional<std::vector<Node>>(3.0, 4.0);
    }
    return result;
}