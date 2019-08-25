#pragma once

#include "Common.h"
#include "Timer.hpp"
#include "Eval.h"
#include "BuildOrder.h"
#include "CombatSearch.h"
#include "CombatSearchParameters.h"
#include "CombatSearchResults.h"
#include "CombatSearch_IntegralData.h"

namespace BOSS
{

class CombatSearch_Integral : public CombatSearch
{
    CombatSearch_IntegralData   _integral;

	void                doSearch(const GameState & s, size_t depth);

public:
	
	CombatSearch_Integral(const CombatSearchParameters p = CombatSearchParameters());
	
    void printResults() override;
    void writeResultsFile(const std::string & filename) override;
};

}