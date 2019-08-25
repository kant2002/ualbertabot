#pragma once
#include "../BaseStrategyExecutor.h"
#include <BWAPI\Player.h>

namespace AKBot
{
	class DragoonRush : public BaseStrategyExecutor
	{
		BWAPI::Player _self;
	public:
		explicit DragoonRush(BWAPI::Player self);
		void getBuildOrderGoal(MetaPairVector& goal, int currentFrame) const final;
	};
}