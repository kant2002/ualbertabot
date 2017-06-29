#pragma once

#include <BWAPI.h>

namespace UAlbertaBot
{

class BotModule
{

public:

    BotModule();

    virtual void onStart() = 0;
    virtual void onFrame() = 0;
    virtual void onEnd(bool isWinner) = 0;
    virtual void onUnitDestroy(BWAPI::Unit unit) = 0;
    virtual void onUnitMorph(BWAPI::Unit unit) = 0;
    virtual void onSendText(std::string text) = 0;
    virtual void onUnitCreate(BWAPI::Unit unit) = 0;
    virtual void onUnitComplete(BWAPI::Unit unit) = 0;
    virtual void onUnitShow(BWAPI::Unit unit) = 0;
    virtual void onUnitHide(BWAPI::Unit unit) = 0;
    virtual void onUnitRenegade(BWAPI::Unit unit) = 0;
};

}