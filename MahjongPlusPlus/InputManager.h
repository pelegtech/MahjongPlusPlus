#pragma once
#include "Raylib.h"
#include "Game.h"
#include "Graphics.h"

class Graphics;
class InputManager {
private:
	Game& game;
public:
	InputManager(Game& game);
	int tileIndexFromClick(const Hand& hand) const;
};