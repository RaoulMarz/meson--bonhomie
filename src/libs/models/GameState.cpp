#include "GameState.h"

void GameState::writeJsonStateFile(std::string outJson, std::ostringstream &outStream) {
    std::ofstream jsonFile(outJson, std::ios::trunc | std::ios::out);
    jsonFile << outStream.str();
}

void GameState::processJsonMap(std::map<std::string, signalr::value> gameStateMap)
{
    std::string exceptionMarker;
    try
    {
        jed_utils::datetime currentTime; //currentTime.to_string()
        Json::Value jsonGameState = signalr::createJson(gameStateMap);
        Json::StreamWriterBuilder builder = signalr::getJsonWriter();
        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        std::ostringstream os;
        writer->write(jsonGameState, &os);
        std::string stateFile = "gamestate_" + currentTime.to_string() + ".json";
        std::string outJsonStateFile = ExtraHelper::combineFilePath("bonhomie-logs", stateFile);
        writeJsonStateFile(outJsonStateFile, os);
        std::map <std::string, bool> sectionKeyMap;
        if (gameStateMap.size() >= 2)
        {
            std::stringstream ss;
            for (const auto &[key, value] : gameStateMap)
            {
                // if (value.is_string())
                //     ss << "[" << key << "]=" << value.as_string() << std::endl;
                ss << "[" << key << "]=";
                ss << SignalRHelper::signalr_value_tostring(value, true, true);

                if (key.compare("populationTiers") == 0) {
                    sectionKeyMap.insert(std::make_pair("populationTiers", true));
                }
                if (key.compare("bots") == 0) {
                    sectionKeyMap.insert(std::make_pair("bots", true));
                }
            }
            exceptionMarker = "iterate map values";
            std::cout << "GameState::processJsonMap = " << std::endl
                      << ss.str();

            std::map<std::string, signalr::value> worldMap;
            if (gameStateMap.find("world")->second.is_map())
                worldMap = gameStateMap.find("world")->second.as_map();
            if (gameStateMap.find("world")->second.is_array())
                worldMap = gameStateMap.find("world")->second.as_array()[0].as_map();
            exceptionMarker = "worldMap extraction";
            world.processJsonMap(worldMap);
            exceptionMarker = "world processJsonMap";
            if (sectionKeyMap.find("populationTiers") != sectionKeyMap.end())
                populationTiers.processJsonMap(gameStateMap.find("populationTiers")->second);
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "GameState::processJsonMap :: exception: " << e.what() << " :: marker = " << exceptionMarker << std::endl;
    }
}