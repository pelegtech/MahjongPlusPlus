#pragma once
#include "Raylib.h"
#include "Core/GameTypes.h"

struct HandTilesLayout;
class CallSelection;
class MeldSelection;
class MoveOption;

class InputManager {
private:
	//Game& game;
public:
	InputManager() = default;
	//InputManager(Game& game);
	int tileIndexFromClick( const HandTilesLayout& handTilesLayout) const;
	MoveType typeFromClick(const CallSelection& selection) const;
	MoveOption OptionFromClick(const MeldSelection& selection) const;
};