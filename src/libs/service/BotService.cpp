#include "BotService.hpp"

/**
 * Main Function to calculate the next action here
 * 
 * PlayerCommand playerCommand;
    GameState gameState;
 */

ScoutTower BotService::chooseOptimalScoutTower(std::vector<ScoutTower> &listTowers) {
   ScoutTower result;
   if (listTowers.size() > 0) {
      if (listTowers.size() == 1)
         return listTowers[0];
      for (ScoutTower xTower : listTowers) {
         //xTower.GetWeighting(??) //get tower (value) weighting based on x factors ...
      }
   }
   return result;
}

void BotService::computeNextPlayerAction(std::promise<void> &startTask) {
    //Fills in the playerCommand instance with the command queue
    std::optional<std::vector<ScoutTower>> scoutTowersList = gameState.world.map.getScoutTowers();
    if (scoutTowersList) {
      chooseOptimalScoutTower(*scoutTowersList);
    }
}

