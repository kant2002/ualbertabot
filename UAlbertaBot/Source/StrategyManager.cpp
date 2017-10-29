#include "Common.h"
#include "StrategyManager.h"
#include "UnitUtil.h"
#include "ParseUtils.h"
#include "FileLogger.h"
#include "strategies\protoss\ZealotRush.h"
#include "strategies\protoss\ZealotDrop.h"
#include "strategies\protoss\DragoonRush.h"
#include "strategies\protoss\DarkTemplarRush.h"
#include "strategies\terrain\MarineRush.h"
#include "strategies\terrain\FourBarracksMarine.h"
#include "strategies\terrain\VultureRush.h"
#include "strategies\terrain\TankPush.h"
#include "strategies\zerg\ZergelingRush.h"
#include "strategies\zerg\TwoHatchHydralisk.h"
#include "strategies\zerg\ThreeHatchMutalisk.h"
#include "strategies\zerg\ThreeHatchScourge.h"

using namespace UAlbertaBot;
using namespace AKBot;

// constructor
StrategyManager::StrategyManager(
	shared_ptr<AKBot::OpponentView> opponentView,
	shared_ptr<UnitInfoManager> unitInfo,
	shared_ptr<BaseLocationManager> bases,
	std::shared_ptr<AKBot::Logger> logger,
	BotStrategyConfiguration& strategyConfiguration)
	: _strategyName("")
	, _opponentView(opponentView)
	, _unitInfo(unitInfo)
	, _bases(bases)
	, _emptyBuildOrder(opponentView->self()->getRace())
	, _logger(logger)
	, _strategyConfiguration(strategyConfiguration)
{
}

void StrategyManager::update()
{

}

const int StrategyManager::getScore(BWAPI::Player player) const
{
	return player->getBuildingScore() + player->getKillScore() + player->getRazingScore() + player->getUnitScore();
}

const BuildOrder & StrategyManager::getOpeningBookBuildOrder() const
{
    auto buildOrderIt = _strategies.find(_strategyName);

    // look for the build order in the build order map
	if (buildOrderIt != std::end(_strategies))
    {
        return (*buildOrderIt).second._buildOrder;
    }
    else
    {
        UAB_ASSERT_WARNING(false, "Strategy not found: %s, returning empty initial build order", _strategyName.c_str());
        return _emptyBuildOrder;
    }
}

const bool StrategyManager::shouldExpandNow(int currentFrame) const
{
	// if there is no place to expand to, we can't expand
	if (_bases->getNextExpansion(_opponentView->self()) == BWAPI::TilePositions::None)
	{
        _logger->log("No valid expansion location");
		return false;
	}

	int frame           = currentFrame;
    int minute          = frame / (24*60);

    // if we have a ridiculous stockpile of minerals, expand
    if (_opponentView->self()->minerals() > 3000)
    {
        return true;
    }

	size_t numDepots = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Command_Center)
		+ UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Nexus)
		+ UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hatchery)
		+ UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Lair)
		+ UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hive);
	
	// we will make expansion N after array[N] minutes have passed
    std::vector<int> expansionTimes = {5, 10, 20, 30, 40 , 50};

    for (size_t i(0); i < expansionTimes.size(); ++i)
    {
        if (numDepots < (i+2) && minute > expansionTimes[i])
        {
            return true;
        }
    }

	return false;
}

void StrategyManager::addStrategy(const std::string & name, Strategy & strategy)
{
    _strategies[name] = strategy;
}

const MetaPairVector StrategyManager::getBuildOrderGoal(int currentFrame) const
{
    auto myRace = _opponentView->self()->getRace();

    if (myRace == BWAPI::Races::Protoss)
    {
        return getProtossBuildOrderGoal(currentFrame);
    }
    else if (myRace == BWAPI::Races::Terran)
	{
		return getTerranBuildOrderGoal(currentFrame);
	}
    else if (myRace == BWAPI::Races::Zerg)
	{
		return getZergBuildOrderGoal(currentFrame);
	}

    return MetaPairVector();
}

const MetaPairVector StrategyManager::getProtossBuildOrderGoal(int currentFrame) const
{
	// the goal to return
	MetaPairVector goal;
	int numNexusCompleted   = _opponentView->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Nexus);
	int numNexusAll         = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Nexus);

    if (_strategyName == "Protoss_ZealotRush")
    {
		ZealotRush zealotRush;
		zealotRush.getBuildOrderGoal(goal, currentFrame);
    }
    else if (_strategyName == "Protoss_DragoonRush")
    {
		DragoonRush dragoonRush;
		dragoonRush.getBuildOrderGoal(goal, currentFrame);
    }
    else if (_strategyName == "Protoss_Drop")
    {
		ZealotDrop zealotDrop;
		zealotDrop.getBuildOrderGoal(goal, currentFrame);
    }
    else if (_strategyName == "Protoss_DTRush")
    {
		DarkTemplarRush darkTemplarRush;
		darkTemplarRush.getBuildOrderGoal(goal, currentFrame);
    }
    else
    {
        UAB_ASSERT_WARNING(false, "Unknown Protoss Strategy Name: %s", _strategyName.c_str());
    }

    // if we have 3 nexus, make an observer
    if (numNexusCompleted >= 3)
    {
        goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Observer, 1));
    }
    
    // add observer to the goal if the enemy has cloaked units
	if (_unitInfo->enemyHasCloakedUnits())
	{
		goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Observer, 1));
	}

    // if we want to expand, insert a nexus into the build order
	if (shouldExpandNow(currentFrame))
	{
		goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Nexus, numNexusAll + 1));
	}

	return goal;
}

const MetaPairVector StrategyManager::getTerranBuildOrderGoal(int currentFrame) const
{
	// the goal to return
	std::vector<MetaPair> goal;

    int numWorkers      = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_SCV);
    int numCC           = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Command_Center);            

    if (_strategyName == "Terran_MarineRush")
    {
		MarineRush marineRush;
		marineRush.getBuildOrderGoal(goal, currentFrame);
    }
    else if (_strategyName == "Terran_4RaxMarines")
    {
		FourBarracksMarine fourBarracksMarine;
		fourBarracksMarine.getBuildOrderGoal(goal, currentFrame);
    }
    else if (_strategyName == "Terran_VultureRush")
    {
		VultureRush vultureRush;
		vultureRush.getBuildOrderGoal(goal, currentFrame);
    }
    else if (_strategyName == "Terran_TankPush")
    {
		TankPush tankPush;
		tankPush.getBuildOrderGoal(goal, currentFrame);
    }
    else
    {
        _logger->log("Warning: No build order goal for Terran Strategy: %s", _strategyName.c_str());
    }

    if (shouldExpandNow(currentFrame))
    {
        goal.push_back(MetaPair(BWAPI::UnitTypes::Terran_Command_Center, numCC + 1));
        goal.push_back(MetaPair(BWAPI::UnitTypes::Terran_SCV, numWorkers + 10));
    }

    if (_unitInfo->enemyHasCloakedUnits())
	{
		goal.push_back(MetaPair(BWAPI::UnitTypes::Terran_Science_Vessel, 1));
	}

	return goal;
}

const MetaPairVector StrategyManager::getZergBuildOrderGoal(int currentFrame) const
{
	// the goal to return
	std::vector<MetaPair> goal;
	
    int numWorkers      = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Drone);
    int numCC           = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hatchery)
                        + UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Lair)
                        + UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hive);
	int numMutas        = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Mutalisk);
    int numDrones       = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Drone);
    int zerglings       = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Zergling);
	int numHydras       = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hydralisk);
    int numScourge      = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Scourge);
    int numGuardians    = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Guardian);

	int mutasWanted = numMutas + 6;
	int hydrasWanted = numHydras + 6;

    if (_strategyName == "Zerg_ZerglingRush")
    {
		ZergelingRush zergelingRush;
		zergelingRush.getBuildOrderGoal(goal, currentFrame);
    }
    else if (_strategyName == "Zerg_2HatchHydra")
    {
		TwoHatchHydralisk twoHatchHydralisk;
		twoHatchHydralisk.getBuildOrderGoal(goal, currentFrame);
    }
    else if (_strategyName == "Zerg_3HatchMuta")
    {
		ThreeHatchMutalisk threeHatchMutalisk;
		threeHatchMutalisk.getBuildOrderGoal(goal, currentFrame);
    }
    else if (_strategyName == "Zerg_3HatchScourge")
    {
		ThreeHatchScourge threeHatchScourge;
		threeHatchScourge.getBuildOrderGoal(goal, currentFrame);
    }
	else
	{
		_logger->log("Warning: No build order goal for Zerg Strategy: %s", _strategyName.c_str());
	}

    if (shouldExpandNow(currentFrame))
    {
        goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Hatchery, numCC + 1));
        goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Drone, numWorkers + 10));
    }

	return goal;
}

void StrategyManager::readResults()
{
    if (!_strategyConfiguration.UsingStrategyIO)
    {
        return;
    }

	// If we don't have any enemy
	auto enemy = _opponentView->defaultEnemy();
	if (enemy == nullptr)
	{
		return;
	}

    std::string enemyName = enemy->getName();
    std::replace(enemyName.begin(), enemyName.end(), ' ', '_');

    std::string enemyResultsFile = _strategyConfiguration.ReadDir + enemyName + ".txt";
    
    std::string strategyName;
    int wins = 0;
    int losses = 0;

    FILE *file = fopen ( enemyResultsFile.c_str(), "r" );
    if ( file != nullptr )
    {
        char line [ 4096 ]; /* or other suitable maximum line size */
        while ( fgets ( line, sizeof line, file ) != nullptr ) /* read a line */
        {
            std::stringstream ss(line);

            ss >> strategyName;
            ss >> wins;
            ss >> losses;

            //_logger.log("Results Found: %s %d %d", strategyName.c_str(), wins, losses);

			auto strategyPtr = _strategies.find(strategyName);
            if (strategyPtr == _strategies.end())
            {
                //_logger.log("Warning: Results file has unknown Strategy: %s", strategyName.c_str());
            }
            else
            {
				auto& strategy = strategyPtr->second;
                strategy._wins = wins;
                strategy._losses = losses;
            }
        }

        fclose ( file );
    }
    else
    {
        //_logger.log("No results file found: %s", enemyResultsFile.c_str());
    }
}

const std::string & UAlbertaBot::StrategyManager::getPreferredStrategy() const
{
	return _strategyName;
}

void StrategyManager::writeResults()
{
    if (!_strategyConfiguration.UsingStrategyIO)
    {
        return;
    }

	auto enemy = _opponentView->defaultEnemy();
	if (enemy == nullptr)
	{
		return;
	}

	std::string enemyName = _opponentView->defaultEnemy()->getName();
    std::replace(enemyName.begin(), enemyName.end(), ' ', '_');

    std::string enemyResultsFile = _strategyConfiguration.WriteDir + enemyName + ".txt";

    std::stringstream ss;

    for (auto & kv : _strategies)
    {
        const Strategy & strategy = kv.second;

        ss << strategy._name << " " << strategy._wins << " " << strategy._losses << "\n";
    }

    Logger::LogOverwriteToFile(enemyResultsFile, ss.str());
}

void StrategyManager::onEnd(const bool isWinner)
{
    if (!_strategyConfiguration.UsingStrategyIO)
    {
        return;
    }

    if (isWinner)
    {
        _strategies[_strategyName]._wins++;
    }
    else
    {
        _strategies[_strategyName]._losses++;
    }

    writeResults();
}

void StrategyManager::setLearnedStrategy()
{
    // we are currently not using this functionality for the competition so turn it off 
    return;

    if (!_strategyConfiguration.UsingStrategyIO)
    {
        return;
    }

    const std::string & strategyName = _strategyName;
    Strategy & currentStrategy = _strategies[strategyName];

    int totalGamesPlayed = 0;
    int strategyGamesPlayed = currentStrategy._wins + currentStrategy._losses;
    double winRate = strategyGamesPlayed > 0 ? currentStrategy._wins / static_cast<double>(strategyGamesPlayed) : 0;

    // if we are using an enemy specific strategy
    if (_strategyConfiguration.FoundEnemySpecificStrategy)
    {        
        return;
    }

    // if our win rate with the current strategy is super high don't explore at all
    // also we're pretty confident in our base strategies so don't change if insufficient games have been played
    if (strategyGamesPlayed < 5 || (strategyGamesPlayed > 0 && winRate > 0.49))
    {
        _logger->log("Still using default strategy");
        return;
    }

    // get the total number of games played so far with this race
    for (auto & kv : _strategies)
    {
        auto& strategy = kv.second;
        if (strategy._race == _opponentView->self()->getRace())
        {
            totalGamesPlayed += strategy._wins + strategy._losses;
        }
    }

    // calculate the UCB value and store the highest
    double C = 0.5;
    std::string bestUCBStrategy;
    double bestUCBStrategyVal = std::numeric_limits<double>::lowest();
    for (auto & kv : _strategies)
    {
        Strategy & strategy = kv.second;
        if (strategy._race != _opponentView->self()->getRace())
        {
            continue;
        }

        int sGamesPlayed = strategy._wins + strategy._losses;
        double sWinRate = sGamesPlayed > 0 ? currentStrategy._wins / static_cast<double>(strategyGamesPlayed) : 0;
        double ucbVal = C * sqrt( log( (double)totalGamesPlayed / sGamesPlayed ) );
        double val = sWinRate + ucbVal;

        if (val > bestUCBStrategyVal)
        {
            bestUCBStrategy = strategy._name;
            bestUCBStrategyVal = val;
        }
    }

    _strategyName = bestUCBStrategy;

	// This is to beckward compatibility to be able change some places later on.
	_strategyConfiguration.StrategyName = bestUCBStrategy;
}

void UAlbertaBot::StrategyManager::setPreferredStrategy(std::string strategy)
{
	_strategyName = strategy;
}
