#pragma once

#include "BOSS.h"
#include "JSONTools.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "BOSSParameters.h"

namespace BOSS
{

class BOSSPlotBuildOrders
{
    std::vector<GameState>      _states;
    std::vector<BuildOrder>     _buildOrders;
    std::vector<std::string>    _buildOrderNames;
    std::string                 _outputDir;

public:

    BOSSPlotBuildOrders(const BOSSParameters& parameters, const std::string & name, const rapidjson::Value & experimentVal);
    
    void doPlots();
};
}
