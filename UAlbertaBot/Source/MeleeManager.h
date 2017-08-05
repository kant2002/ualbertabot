#pragma once;

#include <Common.h>
#include "MicroManager.h"

namespace UAlbertaBot
{
class MicroManager;

class MeleeManager : public MicroManager
{

public:

	MeleeManager(shared_ptr<AKBot::OpponentView> opponentView, shared_ptr<BaseLocationManager> bases);
	void executeMicro(const std::vector<BWAPI::Unit> & targets, int currentFrame);

	int getAttackPriority(BWAPI::Unit attacker, BWAPI::Unit unit);
	BWAPI::Unit getTarget(BWAPI::Unit meleeUnit, const std::vector<BWAPI::Unit> & targets);
    bool meleeUnitShouldRetreat(BWAPI::Unit meleeUnit, const std::vector<BWAPI::Unit> & targets);
    std::pair<BWAPI::Unit, BWAPI::Unit> findClosestUnitPair(const std::vector<BWAPI::Unit> & attackers, const std::vector<BWAPI::Unit> & targets);

    void assignTargets(const std::vector<BWAPI::Unit> & targets, int currentFrame);
};
}