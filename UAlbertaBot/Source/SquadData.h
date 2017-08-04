#pragma once

#include "Squad.h"
#include "Logger.h"

namespace UAlbertaBot
{
class SquadData
{
	std::map<std::string, Squad> _squads;
	UnitHandler onRemoveHandler;
	const AKBot::Logger& _logger;

    void    updateAllSquads(const MapTools& map, int currentFrame);
    void    verifySquadUniqueMembership();
	AKBot::PlayerLocationProvider& _locationProvider;
	const AKBot::OpponentView& _opponentView;
	const UnitInfoManager& _unitInfo;
	const BaseLocationManager& _bases;
	const MapTools& _mapTools;

public:

	SquadData(
		AKBot::PlayerLocationProvider& locationProvider,
		const AKBot::OpponentView& opponentView,
		const UnitInfoManager& unitInfo,
		const BaseLocationManager& bases,
		const MapTools& mapTools,
		const AKBot::Logger& logger);

    void            clearSquadData(int currentFrame);

    bool            canAssignUnitToSquad(BWAPI::Unit unit, const Squad & squad) const;
    void            assignUnitToSquad(BWAPI::Unit unit, Squad & squad);
    void            addSquad(const std::string & squadName, Squad & squad);
	void            addSquad(const std::string & squadName, const SquadOrder & squadOrder, size_t priority);
    void            removeSquad(const std::string & squadName, int currentFrame);

    void            update(const MapTools& map, int currentFrame);

    bool            squadExists(const std::string & squadName);
    bool            unitIsInSquad(BWAPI::Unit unit) const;
    const Squad *   getUnitSquad(BWAPI::Unit unit) const;
    Squad *         getUnitSquad(BWAPI::Unit unit);

    Squad &         getSquad(const std::string & squadName);
    const std::map<std::string, Squad> & getSquads() const;

	void onUnitRemoved(UnitHandler handler);
};
}