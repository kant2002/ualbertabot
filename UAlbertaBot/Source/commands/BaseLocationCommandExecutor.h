#pragma once
#include "CommandExecutor.h"
#include "..\BotConfiguration.h"

namespace AKBot
{
	class BaseLocationCommandExecutor : public CommandExecutor
	{
		BotDebugConfiguration& _debugConfiguration;
	public:
		explicit BaseLocationCommandExecutor(BotDebugConfiguration& debugConfiguration);
		void onCommand(const std::string& command) override;
		bool isSupported(const std::string& command) const override;
	};
}