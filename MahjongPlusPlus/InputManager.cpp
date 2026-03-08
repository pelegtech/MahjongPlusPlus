#include "InputManager.h"
#include "TileGraphics.h"

InputManager::InputManager(Game& game) :game(game){}
int InputManager::tileIndexFromClick() const {
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePos = GetMousePosition();
		return HandTilesRenderer::getTileIndexFromPosition(mousePos);
	}
	return -1;
}
