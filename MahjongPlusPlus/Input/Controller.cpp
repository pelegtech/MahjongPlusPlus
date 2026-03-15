#include "Input/Controller.h"
#include "Input/InputManager.h"
#include "Layouts/TilesLayouts.h"
#include "Core/Hand.h"

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
