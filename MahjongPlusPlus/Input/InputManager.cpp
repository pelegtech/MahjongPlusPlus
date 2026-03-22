#include "Input/InputManager.h"
#include "Layouts/TileLayouts.h"
#include "raylib.h"
#include "UI/CallSelection.h"
#include "UI/MeldSelection.h"
#include "Core/MoveOption.h"

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

MoveType InputManager::typeFromClick(const CallSelection& selection) const
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePos = GetMousePosition();
		MoveType res = selection.typeFromPosition(mousePos);
		return res;
	}
	return MoveType::WAITING;
}

MoveOption InputManager::OptionFromClick(const MeldSelection& selection) const
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePos = GetMousePosition();
		MoveOption res = selection.optionFromPosition(mousePos);
		return res;
	}
	return MoveOption(MoveType::WAITING);
}
