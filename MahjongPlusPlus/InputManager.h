#pragma once
#include "Raylib.h"
#include "Game.h"

struct  HandTilesLayout;

class InputManager {
private:
	//Game& game;
public:
	InputManager() = default;
	//InputManager(Game& game);
	int tileIndexFromClick( const HandTilesLayout& handTilesLayout) const;
};