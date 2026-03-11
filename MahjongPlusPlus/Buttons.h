#pragma once
#include "raylib.h"
#include <string>
#include "GameTypes.h"

class Button {
public:
	Button(Vector2 position, std::string text, MoveType move);

	Button(Rectangle rec, std::string text, MoveType move);

	const Rectangle& getRec() const;

	MoveType getMoveType() const;

	void draw() const;

	static constexpr int DEFAULT_WIDTH = 100;

	static constexpr int DEFAULT_HEIGHT = 50;

	static constexpr int FONT_SIZE = 20;

	static constexpr float OUTLINE_THICKNESS = 2.0f;

private:
	
	Rectangle rec;
	std::string text;
	MoveType move;
};