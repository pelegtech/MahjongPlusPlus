#include "UI/Button.h"

Button::Button()
{
	move = MoveType::WAITING;
	rec = { 0.0f,0.0f,-1.0f,-1.0f };

}

Button::Button(std::string text, Vector2 position, MoveType move) : text(text), move(move)
{
	rec.x = position.x;
	rec.y = position.y;
	rec.width = DEFAULT_WIDTH;
	rec.height = DEFAULT_HEIGHT;
}

Button Button::InaccessibleButton()
{
	Rectangle res = { 0.0f,0.0f,-1.0f,-1.0f };
	return Button("",res,MoveType::WAITING);
}

Button::Button(std::string text, Rectangle rec, MoveType move) : rec(rec), text(text), move(move) {}

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


