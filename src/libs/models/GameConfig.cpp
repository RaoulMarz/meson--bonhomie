#include "GameConfig.h"

GameConfig::GameConfig()
{
    initConfigNumberCategory();
}

void GameConfig::writeJsonConfigFile(std::string outJson, std::ostringstream &outStream)
{
    std::ofstream jsonFile(outJson, std::ios::trunc | std::ios::out);
    jsonFile << outStream.str();
}

void GameConfig::processJsonMap(std::map<std::string, signalr::value> configMap)
{
    jed_utils::datetime currentTime;
    Json::Value jsonGameConfig = signalr::createJson(configMap);
    Json::StreamWriterBuilder builder = signalr::getJsonWriter();
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    std::ostringstream os;
    writer->write(jsonGameConfig, &os);
    std::string configFile = "config_" + currentTime.to_string() + ".json";
    std::string outJsonConfigFile = ExtraHelper::combineFilePath("bonhomie-logs", configFile);
    writeJsonConfigFile(outJsonConfigFile, os);
    if (configMap.size() >= 2)
    {
        std::stringstream ss;
        std::map<std::string, bool> sectionKeyMap;
        for (const auto &[key, value] : configMap)
        {
            ss << "[" << key << "]=";
            ss << SignalRHelper::signalr_value_tostring(value, true, true);
            if (key.compare("botCount") == 0)
            {
                sectionKeyMap.insert(std::make_pair("botCount", true));
            }
            if (key.compare("tickRate") == 0)
            {
                sectionKeyMap.insert(std::make_pair("tickRate", true));
            }
            if (key.compare("startingUnits") == 0)
            {
                sectionKeyMap.insert(std::make_pair("startingUnits", true));
            }
            if (key.compare("startingFood") == 0)
            {
                sectionKeyMap.insert(std::make_pair("startingFood", true));
            }
            if (key.compare("regionSize") == 0)
            {
                sectionKeyMap.insert(std::make_pair("regionSize", true));
            }
            if (key.compare("baseZoneSize") == 0)
            {
                sectionKeyMap.insert(std::make_pair("baseZoneSize", true));
            }
            if (key.compare("scoutWorkTime") == 0)
            {
                sectionKeyMap.insert(std::make_pair("scoutWorkTime", true));
            }
            if (key.compare("maxTicks") == 0)
            {
                sectionKeyMap.insert(std::make_pair("maxTicks", true));
            }
            if (key.compare("minimumPopulation") == 0)
            {
                sectionKeyMap.insert(std::make_pair("minimumPopulation", true));
            }
            if (key.compare("processTick") == 0)
            {
                sectionKeyMap.insert(std::make_pair("processTick", true));
            }
            if (key.compare("numberOfRegionsInMapLength") == 0)
            {
                sectionKeyMap.insert(std::make_pair("numberOfRegionsInMapLength", true));
            }
            if (key.compare("minimumUnits") == 0)
            {
                sectionKeyMap.insert(std::make_pair("minimumUnits", true));
            }
            if (key.compare("worldArea") == 0)
            {
                sectionKeyMap.insert(std::make_pair("worldArea", true));
            }
            if (key.compare("worldLength") == 0)
            {
                sectionKeyMap.insert(std::make_pair("worldLength", true));
            }
            if (key.compare("worldSeed") == 0)
            {
                sectionKeyMap.insert(std::make_pair("worldSeed", true));
            }
        }
        std::cout << "GameConfig::processJsonMap = " << std::endl
                  << ss.str();

        if (sectionKeyMap.size() > 0)
        {
            for (const auto &[sectKey, sectValue] : sectionKeyMap)
            {
                signalr::value cfgItem = configMap[sectKey];
                if (isNumberValue(sectKey))
                {
                }
            }
        }
        // std::map<std::string, signalr::value> worldMap = configMap.find("world")->second.as_map();
        // world.processJsonMap(worldMap);
    }
}

void GameConfig::initConfigNumberCategory()
{
    configCategoryNumbers = {"startingUnits", "startingFood", "regionSize", "baseZoneSize", "scoutWorkTime",
                             "maxTicks", "minimumPopulation", "processTick", "numberOfRegionsInMapLength",
                             "minimumUnits", "worldArea", "worldLength", "worldSeed"
    };
}

// Values like "maxTicks", "scoutWorkTime"
bool GameConfig::isNumberValue(std::string configKey)
{
    bool res = false;
    return res;
}