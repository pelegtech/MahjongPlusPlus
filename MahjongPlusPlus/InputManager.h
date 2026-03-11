#pragma once
#include "Raylib.h"
#include "Game.h"
#include "Graphics.h"

class Graphics;
class InputManager {
private:
	//Game& game;
public:
	InputManager() = default;
	//InputManager(Game& game);
	int tileIndexFromClick( const HandTilesLayout& handTilesLayout) const;
};