#ifndef CPPBOT_WORLD_WORLDAMEOBJECT_H
#define CPPBOT_WORLD_WORLDAMEOBJECT_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include "SignalRHelper.h"
#include "signalrclient/signalr_value.h"
#include "Map.h"

class World
{
    public:
    int size;
    int currentTick;
    Map map;

    void processJsonMap(std::map<std::string, signalr::value> worldMap);
};

#endif //CPPBOT_WORLD_WORLDAMEOBJECT_H
