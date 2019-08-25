#include "BOSSExperiments.h"

#include "CombatSearchExperiment.h"
#include "BOSSPlotBuildOrders.h"

using namespace BOSS;

void Experiments::RunExperiments(const BOSSParameters& parameters, const std::string & experimentFilename)
{
    rapidjson::Document document;
    JSONTools::ParseJSONFile(document, experimentFilename);

    BOSS_ASSERT(document.HasMember("Experiments"), "No 'Experiments' member found");

    const rapidjson::Value & experiments = document["Experiments"];
    for (rapidjson::Value::ConstMemberIterator itr = experiments.MemberBegin(); itr != experiments.MemberEnd(); ++itr)
    {
        const std::string &         name = itr->name.GetString();
        const rapidjson::Value &    val  = itr->value;
        
        //std::cout << "Found Experiment:   " << name << std::endl;
        BOSS_ASSERT(val.HasMember("Type") && val["Type"].IsString(), "Experiment has no 'Type' string");

        if (val.HasMember("Run") && val["Run"].IsBool() && (val["Run"].GetBool() == true))
        {   
            const std::string & type = val["Type"].GetString();

            if (type == "CombatSearch")
            {
                RunCombatExperiment(parameters, name, val);
            }
            else if (type == "BuildOrderPlot")
            {
                RunBuildOrderPlot(parameters, name, val);
            }
            else
            {
                BOSS_ASSERT(false, "Unknown Experiment Type: %s", type.c_str());
            }
        }
    }

    std::cout << "\n\n";
}

void Experiments::RunCombatExperiment(const BOSSParameters& parameters, const std::string & name, const rapidjson::Value & val)
{
    CombatSearchExperiment exp(parameters, name, val);
    exp.run();
}

void Experiments::RunBuildOrderPlot(const BOSSParameters& parameters, const std::string & name, const rapidjson::Value & val)
{
    BOSSPlotBuildOrders plot(parameters, name, val);
    plot.doPlots();
}