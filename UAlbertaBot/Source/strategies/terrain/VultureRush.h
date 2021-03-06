#pragma once
#include "../BaseStrategyExecutor.h"
#include <BWAPI\Player.h>

namespace AKBot
{
	class VultureRush : public BaseStrategyExecutor
	{
		BWAPI::Player _self;
	public:
		explicit VultureRush(BWAPI::Player self);
		void getBuildOrderGoal(MetaPairVector& goal, int currentFrame) const final;
	};
}