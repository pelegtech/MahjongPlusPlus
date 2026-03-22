#include "CallSelection.h"
#include "Core/MoveOption.h"
#include "UI/Button.h"


void CallSelection::update(const std::vector<MoveOption>& options)
{
	
	existingTypes.fill(false);
	for (const MoveOption& option : options) {
		existingTypes[static_cast<int>(option.getType())] = true;
	}
	for (int i = 0; i < buttons.size(); i++) {
		if (existingTypes[i]) {
			buttons[i] = Button(TYPE_NAMES[i], BUTTON_POSITIONS[i], static_cast<MoveType>(i));
		}
		else {
			buttons[i] = Button::InaccessibleButton();
		}
	}
	int skip = static_cast<int>(MoveType::SKIP);
	existingTypes[skip] = true;
	buttons[skip] = Button(TYPE_NAMES[skip], BUTTON_POSITIONS[skip], (MoveType::SKIP));
}

void CallSelection::draw() const
{
	for (int i = 0; i < buttons.size(); i++) {
		if (existingTypes[i]) {
			buttons[i].draw();
		}
	}
}

MoveType CallSelection::typeFromPosition(Vector2 pos) const
{
	for (int i = 0; i < buttons.size(); i++) {
		if (CheckCollisionPointRec(pos,buttons[i].getRec())) {
			return static_cast<MoveType>(i);
		}
	}
	return MoveType::WAITING;
}
