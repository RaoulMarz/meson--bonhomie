#ifndef CPPBOT_POPULATION_TIER_H
#define CPPBOT_POPULATION_TIER_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include "SignalRHelper.h"
#include "signalrclient/signalr_value.h"

class PopulationTier
{
    private:
        int level;
        int maxPopulation;
        std::pair<float, float> populationChangeFactorRange;
    public:

    void processJsonMap(signalr::value startNode);
    void setLevel(int level);
    void setMaxPopulation(int maxPop);
    void setPopulationChangeFactor(std::pair<float, float> popChangeFactorRng);
};

#endif //CPPBOT_POPULATION_TIER_H