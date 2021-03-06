#pragma once

#include "ArenaPlayer.h"
#include <BWAPI/Unit.h>
#include "OpponentView.h"

namespace UAlbertaBot
{
	using AKBot::OpponentView;

class ArenaPlayer_AttackClosest : public ArenaPlayer
{
	std::shared_ptr<OpponentView> _opponentView;
    BWAPI::Unit getClosestEnemyUnit(BWAPI::Unit ourUnit) const;

public:

	explicit ArenaPlayer_AttackClosest(std::shared_ptr<OpponentView> opponentView);

    void onStart() override;
    void onFrame(int currentFrame) override;
    void onBattleBegin() override;
    void onBattleEnd() override;
};
}