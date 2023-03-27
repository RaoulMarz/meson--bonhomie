#ifndef CPPBOT_NODE_H
#define CPPBOT_NODE_H

#include <iostream>
#include "Position.h"
#include "RegenerationRate.h"

//
// Created by megan.humphreys on 2022/03/21.
//

struct Node
{
    int type;
    int amount;
    int maxUnits;
    int currentUnits;
    int reward;
    int workTime;
    std::string id;
    int gameObjectType;
    Position position;
    RegenerationRate positionRate;
};

#endif //CPPBOT_NODE_H
