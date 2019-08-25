#pragma once

#include "Common.h"
#include "JSONTools.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "BOSSParameters.h"

namespace BOSS
{

namespace Experiments
{
    void RunExperiments(const BOSSParameters& parameters, const std::string & experimentFilename);

    void RunCombatExperiment(const BOSSParameters& parameters, const std::string & name, const rapidjson::Value & val);
    void RunBuildOrderPlot(const BOSSParameters& parameters, const std::string & name, const rapidjson::Value & val);
}

}