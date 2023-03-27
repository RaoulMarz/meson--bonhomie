#ifndef PLAYER_ACTION_H
#define PLAYER_ACTION_H

#include <string>
#include <sstream>
#include "ActionTypes.h"

//
// Created by megan.humphreys on 2022/03/21.
//

// Example format: [{"Type":1,"Units":1,"TargetNode":{"x":18,"y":18}}]}

class PlayerAction
{
    public:
    ActionTypes type;
    int units;
    std::string id;

/*
Error = 0,
    Scout = 1,
    Mine = 2,
    Farm = 3,
    Lumber = 4
*/
    std::string printEnumType(ActionTypes type) {
        std::string res = "";
        switch (type)
        {
        case ActionTypes::Error :
            res = "Error";
            break;
        case ActionTypes::Scout :
            res = "Scout";
            break;
        case ActionTypes::Mine :
            res = "Mine";
            break;
        case ActionTypes::Farm :
            res = "Farm";
            break;
        case ActionTypes::Lumber :
            res = "Lumber";
            break;
        default:
            break;
        }
        return res;
    }

    std::string toString() {
        std::stringstream ss;
        ss << "[PlayerAction] :: id = " << id << " , units = " << units << " , type = " << printEnumType(type) << std::endl;
        return ss.str();
    }
};

#endif //PLAYER_ACTION_H
