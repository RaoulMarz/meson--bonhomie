#include "PopulationTier.h"

void PopulationTier::processJsonMap(signalr::value startNode)
{
    std::string exceptionMarker;
    try
    {
        std::stringstream ss;
        if (startNode.is_array())
        {
            // gameMap = worldMap.find("map")->second.as_array()[0].as_map();
            /*
            if (gameMap.size() >= 2) {
                for (const auto &[key, value] : gameMap)
                {
                }
            }
            */
           std::vector<signalr::value> vectorValues = startNode.as_array();
           for (signalr::value childItem : vectorValues) {
                std::map<std::string, signalr::value> popTierMap = childItem.as_map();
                if (popTierMap.size() > 0) {
                    for (const auto &[key, value] : popTierMap) {
                    }
                }
           }
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "PopulationTier::processJsonMap :: exception: " << e.what() << " :: marker = " << exceptionMarker << std::endl;
    }
}

void PopulationTier::setLevel(int level)
{
}

void PopulationTier::setMaxPopulation(int maxPop)
{
}

void PopulationTier::setPopulationChangeFactor(std::pair<float, float> popChangeFactorRng)
{
}