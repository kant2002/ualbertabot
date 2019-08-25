#pragma once
#include "OpponentView.h"
#include <BWAPI/Game.h>

namespace AKBot
{
	/*
	 Provide view to the bot opponents using BWAPI
	*/
	class BWAPIOpponentView : public OpponentView
	{
		BWAPI::Game* _game;
	public:
		/*
		* Initialize new instance of the @see BWAPIOpponentView class
		* @param game BWAPI game
		*/
		explicit BWAPIOpponentView(BWAPI::Game* game) noexcept;
		/*
		Returns bot's player
		*/
		BWAPI::Player self() const override;

		/*
		Default enemy for current player
		*/
		BWAPI::Player defaultEnemy() const override;

		/*
		Returns set of opponents to the given bot.
		*/
		const BWAPI::Playerset& enemies() const override;
	};
}