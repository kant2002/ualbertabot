#include "BWAPIOpponentView.h"
#include <BWAPI\Game.h>
#include <boost/range/algorithm/find_if.hpp>

AKBot::BWAPIOpponentView::BWAPIOpponentView(BWAPI::Game* game) noexcept: _game(game)
{
}

BWAPI::Player AKBot::BWAPIOpponentView::self() const
{
	return _game->self();
}

BWAPI::Player AKBot::BWAPIOpponentView::defaultEnemy() const
{
	const auto defaultEnemy = _game->enemy();
	if (defaultEnemy == nullptr)
	{
		return nullptr;
	}

	if (defaultEnemy->leftGame() || defaultEnemy->isDefeated())
	{
		const auto foundEnemy = boost::find_if(_game->enemies(), [](const auto& enemy) {
			return !enemy->leftGame() && !enemy->isDefeated();
		});
		if (foundEnemy != boost::end(_game->enemies()))
		{
			return *foundEnemy;
		}
	}

	return defaultEnemy;
}

const BWAPI::Playerset & AKBot::BWAPIOpponentView::enemies() const
{
	return _game->enemies();
}
