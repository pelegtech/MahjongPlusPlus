#pragma once
#include "raylib.h"
#include <string>
#include "Core/GameTypes.h"

class Button {
public:

	Button();

	Button(std::string text, Vector2 position, MoveType move);

	static Button InaccessibleButton();

	explicit Button(std::string text, Rectangle rec, MoveType move) ;

	const Rectangle& getRec() const;

	MoveType getMoveType() const;

	void draw() const;

	static constexpr int DEFAULT_WIDTH = 100;

	static constexpr int DEFAULT_HEIGHT = 50;

	static constexpr int FONT_SIZE = 20;

	static constexpr float OUTLINE_THICKNESS = 2.0f;

private:
	std::string text;
	MoveType move;
	Rectangle rec;
};