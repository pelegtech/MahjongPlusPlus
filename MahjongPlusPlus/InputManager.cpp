#include "InputManager.h"

InputManager::InputManager(Game& game) :game(game){}
int InputManager::tileIndexFromClick() const {
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePos = GetMousePosition();
		return Graphics::getTileIndexFromPosition(mousePos);
	}
	return -1;
}
