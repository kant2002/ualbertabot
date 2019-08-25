#pragma once

#include "BOSS.h"
#include "JSONTools.h"
#include <memory>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "BOSSParameters.h"

namespace BOSS
{

class CombatSearchExperiment
{
    std::string                 _name;
    CombatSearchParameters      _params;
    RaceID                      _race;
    std::vector<std::string>    _searchTypes;

    RaceID                      _enemyRace;
    BuildOrder                  _enemyBuildOrder;

public:

    CombatSearchExperiment();
    CombatSearchExperiment(const BOSSParameters& parameters, const std::string & name, const rapidjson::Value & experimentVal);

    void run();
};
}
