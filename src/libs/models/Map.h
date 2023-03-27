#ifndef CPPBOT_MAP_H
#define CPPBOT_MAP_H

#include <vector>
#include <map>
#include <optional>
#include <string>
#include <sstream>
#include "signalrclient/signalr_value.h"
#include "SignalRHelper.h"
#include "ScoutTower.h"
#include "Node.h"

//
// Created by megan.humphreys on 2022/03/21.
//

class Map
{
private:
    //std::map<std::string, signalr::value> mapScoutTowers;
    //std::map<std::string, signalr::value> mapNodes;
    std::vector<signalr::value> vectorScoutTowers;
    std::vector<signalr::value> vectorNodes;
    std::vector<signalr::value> vectorAvailableNodes;

public:
    std::vector<ScoutTower> scoutTowers;
    std::vector<Node> nodes;

    void processJsonMap(std::map<std::string, signalr::value> gameMap);
    std::optional<std::vector<ScoutTower>> getScoutTowers();
    std::optional<std::vector<Node>> getNodes();
};

#endif // CPPBOT_MAP_H
