#ifndef CPPBOT_GAMESTATE_H
#define CPPBOT_GAMESTATE_H

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "datetime.h"
#include "signalrclient/signalr_value.h"
#include "SignalRHelper.h"
#include "json_helpers.h"
#include "extrahelper.h"
#include "World.h"
#include "Bot.h"
#include "PopulationTier.h"

class GameState
{
    private:
        void writeJsonStateFile(std::string outJson, std::ostringstream &outStream);
    public:
    World world;
    PopulationTier populationTiers;
    std::vector<Bot> bots;

    void processJsonMap(std::map<std::string, signalr::value> gameStateMap);
};

#endif //CPPBOT_GAMESTATE_H
