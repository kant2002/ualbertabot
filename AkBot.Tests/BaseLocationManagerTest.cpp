#include <direct.h>
#define BOOST_TEST_MODULE BaseLocationManagerTest
#include <boost/test/included/unit_test.hpp>
#include "BaseLocationManager.h"
#include "GameImpl.h"
#include "BWAPIOpponentView.h"
#include "BWAPIMapInformation.h"
#include "MapTools.h"
#include "SupportLib/NullLogger.h"
#include "SupportLib/PlainOpponentView.h"
#include "SupportLib/UnitHelper.h"
#include "SupportLib/GameHelper.h"
#include "SupportLib/GameBuilder.h"
#include "SupportLib/BWAPISession.h"
#include "basedetection/ClusterBaseDetector.h"

using namespace AKBot::Tests;
using namespace AkBotTests;
using AKBot::OpponentView;
using AKBot::PlainOpponentView;
using AKBot::BWAPIOpponentView;
using AKBot::BWAPIMapInformation;
using UAlbertaBot::MapTools;

BOOST_AUTO_TEST_CASE(CreationOfBaseLocationManagerWithEmptyData)
{
	AKBot::Tests::GameBuilder builder;
	auto game = builder.getGame();
	BWAPISession session(game);

	auto opponentView = std::make_shared<BWAPIOpponentView>(game);
	BotBaseDetectionConfiguration configuration;
	UAlbertaBot::BaseLocationManager manager(game, opponentView, configuration);
}

BOOST_AUTO_TEST_CASE(CreationOfBaseLocationManagerFromEmptyResources)
{
	BotBaseDetectionConfiguration configuration;
	AKBot::Tests::GameBuilder builder;
	builder.setP2PForces()
		.setPlayers(2)
		.setupEmptyMap(100, 100);

	auto game = builder.getGame();
	BWAPISession session(game);

	auto opponentView = std::make_shared<BWAPIOpponentView>(BWAPIOpponentView(game));
	UAlbertaBot::BaseLocationManager manager(game, opponentView, configuration);
	auto mapInformation = std::make_shared<BWAPIMapInformation>(game);
	auto logger = std::make_shared<NullLogger>();
	auto mapTools = std::make_shared<MapTools>(mapInformation, logger);
	manager.registerBaseDetector(
		"uab",
		std::make_unique<AKBot::ClusterBaseDetector>(
			game,
			opponentView,
			mapTools));
	auto baseLocations = std::vector<UAlbertaBot::BaseLocation>();

	game->onMatchStart();
	manager.getCurrentBaseDetector().detectBases(baseLocations);
	BOOST_TEST(0U == baseLocations.size(), L"The base locations list should be empty");
}

BOOST_AUTO_TEST_CASE(ClustersWith4MineralsCounted)
{
	AKBot::Tests::GameBuilder builder;
	builder.setP2PForces()
		.setPlayers(2)
		.setupEmptyMap(100, 100);

	// Create cluster of 4 minerals
	builder
		.discoverMineral(1, 1, 200)
		.discoverMineral(2, 1, 200)
		.discoverMineral(3, 1, 200)
		.discoverMineral(4, 1, 200);

	auto game = builder.getGame();
	BWAPISession session(game);

	auto opponentView = std::make_shared<BWAPIOpponentView>(BWAPIOpponentView(game));
	BotBaseDetectionConfiguration configuration;
	UAlbertaBot::BaseLocationManager manager(game, opponentView, configuration);
	auto mapInformation = std::make_shared<BWAPIMapInformation>(game);
	auto logger = std::make_shared<NullLogger>();
	auto mapTools = std::make_shared<MapTools>(mapInformation, logger);
	manager.registerBaseDetector(
		"uab",
		std::make_unique<AKBot::ClusterBaseDetector>(
			game,
			opponentView,
			mapTools));
	auto baseLocations = std::vector<UAlbertaBot::BaseLocation>();

	game->onMatchStart();
	manager.getCurrentBaseDetector().detectBases(baseLocations);
	BOOST_TEST(1U == baseLocations.size(), L"The base locations list should be empty");
}

BOOST_AUTO_TEST_CASE(ClustersCouldContainMineralsAndGeysers)
{
	AKBot::Tests::GameBuilder builder;
	builder.setP2PForces()
		.setPlayers(2)
		.setupEmptyMap(100, 100);

	// Create cluster of 4 minerals
	builder
		.discoverMineral(1, 1, 200)
		.discoverMineral(2, 1, 200)
		.discoverMineral(3, 1, 200)
		.discoverGeyser(4, 1, 200);

	auto game = builder.getGame();
	BWAPISession session(game);

	BotBaseDetectionConfiguration configuration;
	auto opponentView = std::make_shared<BWAPIOpponentView>(BWAPIOpponentView(game));
	UAlbertaBot::BaseLocationManager manager(game, opponentView, configuration);
	auto mapInformation = std::make_shared<BWAPIMapInformation>(game);
	auto logger = std::make_shared<NullLogger>();
	auto mapTools = std::make_shared<MapTools>(mapInformation, logger);
	manager.registerBaseDetector(
		"uab",
		std::make_unique<AKBot::ClusterBaseDetector>(
			game,
			opponentView,
			mapTools));
	auto baseLocations = std::vector<UAlbertaBot::BaseLocation>();

	game->onMatchStart();
	manager.getCurrentBaseDetector().detectBases(baseLocations);
	BOOST_TEST(1U == baseLocations.size(), L"The base locations list should be empty");
}