#pragma once

#include "DebugInfoProvider.h"
#include "..\GameCommander.h"
#include "..\HUDInfo.h"
#include "..\ScreenCanvas.h"

namespace AKBot
{
	using UAlbertaBot::GameCommander;

	class GameCommanderDebug : public DebugInfoProvider
	{
		shared_ptr<GameCommander> _gameCommander;
		shared_ptr<AKBot::Logger> _logger;
		shared_ptr<HUDInfo> _hudInfo;
		const BotDebugConfiguration& _debugConfiguration;
		const BotStrategyConfiguration& _strategyConfiguration;

		void drawGameInformation(ScreenCanvas& canvas, int currentFrame, int x, int y) const;
	public:
		GameCommanderDebug(
			shared_ptr<GameCommander> gameCommander,
			shared_ptr<AKBot::Logger> logger,
			shared_ptr<HUDInfo> hudInfo,
			const BotDebugConfiguration& debugConfiguration,
			const BotStrategyConfiguration& strategyConfiguration);
		GameCommanderDebug(const GameCommanderDebug&) = delete;
		void draw(ScreenCanvas& canvas, int currentFrame) override;
	};
}
