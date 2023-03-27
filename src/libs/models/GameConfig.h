#ifndef GAMECONFIG_WORLDGAMEOBJECT_H
#define GAMECONFIG_WORLDGAMEOBJECT_H

#include <iostream>
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

class GameConfig
{
    private:
        std::vector<std::string> configCategoryNumbers;

        bool isNumberValue(std::string configKey);
        void initConfigNumberCategory();
        void writeJsonConfigFile(std::string outJson, std::ostringstream &outStream);
    public:
    GameConfig();

    int startingUnits;
    int startingFood;
    int regionSize;
    int baseZoneSize;
    int scoutWorkTime;
    int maxTicks;
    int minimumPopulation;
    int minimumUnits;
    int worldArea;
    int worldLength;
    int worldSeed;

    int processTick;
    int numberOfRegionsInMapLength;

    void processJsonMap(std::map<std::string, signalr::value> configMap);
};

#endif //GAMECONFIG_WORLDGAMEOBJECT_H