#pragma once

#include "../Common.h"
#include "../GameState.h"

#include "TorchFrame.h"
#include <istream>
#include "../AIParameters.h"

namespace SparCraft
{
namespace TorchTools
{
	GameState GetSparCraftStateFromTorchCraftFrame(const replayer::Frame & frame);
	GameState GetSparCraftStateFromTorchCraftFrameStream(std::istream & in);
	GameState GetSparCraftStateFromTorchCraftFrameFile(const std::string & filename);

    void PrintStateValueFromFrameStream(const AIParameters& aiParameters, std::istream & sin);
    void PrintMoveFromFrameStream(const AIParameters& aiParameters, std::istream & in);
    Move GetMove(const GameState & state, const size_t & playerID, const std::string & aiPlayerName);
    std::string GetMoveStringLUA(const GameState & state, const Move & move);
}
}
