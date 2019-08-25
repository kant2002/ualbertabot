#pragma once
#include "../BaseStrategyExecutor.h"
#include <BWAPI\Player.h>

namespace AKBot
{
	class ZergelingRush : public BaseStrategyExecutor
	{
		BWAPI::Player _self;
	public:
		explicit ZergelingRush(BWAPI::Player self);
		void getBuildOrderGoal(MetaPairVector& goal, int currentFrame) const final;
	};
}