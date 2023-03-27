#ifndef CPPBOT_BOTSERVICE_HPP
#define CPPBOT_BOTSERVICE_HPP

#include <vector>
#include <iostream>
#include <optional>
#include <chrono>
#include <thread>
#include <future>
#include "GameInfoLogger.h"
#include "PlayerCommand.h"
#include "GameState.h"
#include "Bot.h"
#include "ScoutTower.h"

class BotService {
private:
    Bot bot;
    PlayerCommand playerCommand;
    GameState gameState;
    GameInfoLogger botLogger;

    bool hasCommand = false;
public:
    void setPlayerId(std::string &id) {
        playerCommand.setPlayerID(id);
    }

    std::optional<PlayerCommand> getPlayerCommand() const
    {
        std::optional<PlayerCommand> result = std::nullopt;
        if (hasCommand)
            result = std::make_optional<PlayerCommand>(playerCommand);
        return result;
    }

    GameState getGameState()
    {
        return gameState;
    }

    Bot getBot() const
    {
        return bot;
    }

    void setBot(Bot& bot)
    {
        this->bot = bot;
    }

    void updateSelfState()
    {
        
    }

    void setGameState(GameState& gameState)
    {
        this->gameState = gameState;
        updateSelfState();
    }

    void setLogger(const GameInfoLogger& botLogger)
    {
        this->botLogger = botLogger;
    }

    GameInfoLogger getLogger() const
    {
        return botLogger;
    }

    void setValidCommand(bool validCmd) {
        hasCommand = validCmd;
    }

    ScoutTower chooseOptimalScoutTower(std::vector<ScoutTower> &listTowers);
    void computeNextPlayerAction(std::promise<void> &startTask);
};

#endif //CPPBOT_BOTSERVICE_HPP
