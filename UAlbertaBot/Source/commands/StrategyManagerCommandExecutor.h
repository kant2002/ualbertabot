
#pragma once
#include "CommandExecutor.h"
#include "../StrategyManager.h"
#include "../BotConfiguration.h"

namespace AKBot
{
	using UAlbertaBot::StrategyManager;

	class StrategyManagerCommandExecutor : public CommandExecutor
	{
		StrategyManager& _strategyManager;
		BotStrategyConfiguration& _strategyConfiguration;
	public:
		StrategyManagerCommandExecutor(
			StrategyManager& strategyManager,
			BotStrategyConfiguration& strategyConfiguration);
		void onCommand(const std::string& command) override;
		bool isSupported(const std::string& command) const override;
	};
}