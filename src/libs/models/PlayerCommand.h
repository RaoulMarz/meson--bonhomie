#ifndef PLAYER_COMMAND_H
#define PLAYER_COMMAND_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <optional>
#include "PlayerAction.h"

// {"PlayerId":"c0f75c6a-fffe-47de-876c-a6f5dbbffda3","Actions":[{"Type":1,"Units":1,"TargetNode":{"x":18,"y":18}}]}

class PlayerCommand {
    private:
    std::string playerId;
    std::vector<PlayerAction> actions;

    public:
    
    std::string getPlayerID() {
        return playerId;
    }

    void setPlayerID(std::string playerID) {
        this->playerId = playerID;
    }

    std::vector<PlayerAction> getActions() {
        return actions;
    }

    void setActions(std::vector<PlayerAction> actions) {
        this->actions = actions;
    }

    std::string getActionsPrinted() {
        std::string res = "";
        std::stringstream ss;
        ss << "PlayerID = " << playerId;
        int actionIdx = 0;
        if (actions.size() > 0) {
            for (PlayerAction xAction : actions) {
                ss << "action[ = " << actionIdx << "] = " << xAction.toString();
                actionIdx += 1;
            }
        }
        res = ss.str();
        return res;
    }
};

#endif //PLAYER_COMMAND_H
