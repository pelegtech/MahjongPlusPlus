#include "Input/InputManager.h"
#include "Layouts/TilesLayouts.h"
#include "raylib.h"

//InputManager::InputManager(Game& game) :game(game){}


int InputManager::tileIndexFromClick( const HandTilesLayout& layout) const
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePos = GetMousePosition();
		for (int i = 0; i < layout.size ; i++) {
			if (CheckCollisionPointRec(mousePos, layout.recs[i])) {
				return i;
			}
		}
	}
	return -1;
}
