#include "Layouts/Buttons.h"

Button::Button(Vector2 position, std::string text, MoveType move): text(text), move(move)
{
	rec.x = position.x;
	rec.y = position.y;
	rec.width = DEFAULT_WIDTH;
	rec.height = DEFAULT_HEIGHT;
}

Button::Button(Rectangle rec, std::string text, MoveType move) : rec(rec), text(text), move(move){}

const Rectangle& Button::getRec() const
{
	return rec;
}

MoveType Button::getMoveType() const
{
	return move;
}

void Button::draw() const
{
	DrawRectangleRec(rec, GRAY);
	DrawRectangleLinesEx(rec, OUTLINE_THICKNESS, BLACK);
	int textWidth = MeasureText(text.c_str(), FONT_SIZE);

	Vector2 textPos = { rec.x + (rec.width - textWidth) / 2, rec.y + (rec.height - FONT_SIZE) / 2 };
	DrawText(text.c_str(), textPos.x, textPos.y, FONT_SIZE, WHITE);
}


