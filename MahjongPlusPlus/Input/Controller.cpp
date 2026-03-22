#include "Input/Controller.h"
#include "Input/InputManager.h"
#include "Layouts/TileLayouts.h"
#include "Core/Hand.h"
#include "Core/MoveOption.h"
#include "Graphics/TileGraphics.h"
#include "UI/MeldSelection.h"
#include "UI/CallSelection.h"
#include "UI/Button.h"


int HumanController::decideDiscard(const HandTilesLayout& layout
	, const InputManager& input) const
{
	return input.tileIndexFromClick(layout);
}

MoveType HumanController::decideTypeAfterDiscard(const InputManager& input,
	const CallSelection& selection) const
{
	return input.typeFromClick(selection);
}

MoveOption HumanController::decideOptionAfterDiscard(const InputManager& input,
	const MeldSelection& selection) const
{
	return input.OptionFromClick(selection);
}

int BotController::decideDiscard(const HandTilesLayout& layout
	, const InputManager& input) const
{
	return 13;
}

MoveType BotController::decideTypeAfterDiscard(const InputManager& input,
	const CallSelection& selection) const
{
	return MoveType::SKIP;
}

MoveOption BotController::decideOptionAfterDiscard(const InputManager& input, const MeldSelection& selection) const
{
	return MoveOption(MoveType::SKIP);
}



