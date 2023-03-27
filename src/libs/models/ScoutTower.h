#ifndef CPPBOT_SCOUTTOWER_H
#define CPPBOT_SCOUTTOWER_H

#include "Position.h"
#include "Node.h"
#include "ObjectTypes.h"
#include <iostream>
#include <vector>

//
// Created by megan.humphreys on 2022/03/21.
//

struct ScoutTower
{
    std::vector<Node> nodes;
    std::string id;
    ObjectTypes gameObjectType;
    Position position;
};

#endif //CPPBOT_SCOUTTOWER_H
