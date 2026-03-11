#include "Controller.h"
#include "InputManager.h"
#include "Layout.h"
#include "Hand.h"

int HumanController::decideDiscard(const Hand& hand,
	const HandTilesLayout & layout, const InputManager& input) const
{
	return input.tileIndexFromClick(layout);
}

int BotController::decideDiscard(const Hand& hand, 
	const HandTilesLayout& layout, const InputManager& input) const
{
	return 0;
}
