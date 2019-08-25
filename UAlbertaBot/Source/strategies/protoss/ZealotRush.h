#pragma once
#include "../BaseStrategyExecutor.h"
#include <BWAPI\Player.h>

namespace AKBot
{
	class ZealotRush: public BaseStrategyExecutor
	{
		BWAPI::Player _self;
	public:
		explicit ZealotRush(BWAPI::Player self);
		void getBuildOrderGoal(MetaPairVector& goal, int currentFrame) const final;
	};
}