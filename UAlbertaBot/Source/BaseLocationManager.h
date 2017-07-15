#pragma once

#include "Common.h"
#include "MetaType.h"
#include "DistanceMap.h"
#include "BaseLocation.h"
#include "Distance.h"

namespace UAlbertaBot
{
	class UnitInfoManager;
	class MapTools;

	/*
		Manage location of the player bases.
	*/
	class BaseLocationManager
	{
		std::vector<BaseLocation>   _baseLocationData;
		const AKBot::OpponentView& _opponentView;

		std::vector<const BaseLocation *> _baseLocationPtrs;
		std::vector<const BaseLocation *> _startingBaseLocations;
		std::map<BWAPI::Player, const BaseLocation *> _playerStartingBaseLocations;
		std::map<BWAPI::Player, std::set<const BaseLocation *>> _occupiedBaseLocations;

		std::vector<std::vector<BaseLocation *>> _tileBaseLocations;  // precomputed base locations for each tile on the map, nullptr if not in a base

		BaseLocation * _getBaseLocation(BWAPI::TilePosition pos) const;
		BaseLocation * _getBaseLocation(BWAPI::Position pos) const;
		// Append list of resource clusters bases on existing resources
		void addNewResourceClusters(
			std::vector<std::vector<BWAPI::Unit>>& resourceClusters,
			const BWAPI::Unitset& resources,
			AKBot::DistanceFunction distanceFunction,
			const int resourceThreshold,
			const int clusterDistance);
		// Add resources to existing clusters
		void addToExistingResourceClusters(
			std::vector<std::vector<BWAPI::Unit>>& resourceClusters,
			const BWAPI::Unitset& resources,
			AKBot::DistanceFunction distanceFunction,
			const int resourceThreshold,
			const int clusterDistance);

		/*
			Reset the player occupation information for each location
		*/
		void resetPlayerOccupation();
	public:

		BaseLocationManager(const AKBot::OpponentView& opponentView);

		void update(const UnitInfoManager & unitManager);
		void onStart(const MapTools& map);

		const std::vector<const BaseLocation *> & getBaseLocations() const;
		const std::vector<const BaseLocation *> & getStartingBaseLocations() const;
		const std::set<const BaseLocation *> & getOccupiedBaseLocations(BWAPI::Player player) const;
		const BaseLocation * getPlayerStartingBaseLocation(BWAPI::Player player) const;
		BWAPI::TilePosition getNextExpansion(BWAPI::Player player) const;

		const BaseLocation * getBaseLocation(BWAPI::TilePosition pos) const;
		const BaseLocation * getBaseLocation(BWAPI::Position pos) const;
	};

}