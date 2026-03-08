#pragma once
static constexpr int SCREEN_WIDTH = 1920;
static constexpr int SCREEN_HEIGHT = 1080;
static constexpr int HAND_TILE_WIDTH = 80;
static constexpr int HAND_TILE_HEIGHT = 129;
static constexpr int HAND_SIZE = 14;
static constexpr Vector2 HAND_POSITION = { 340,900 };
static constexpr int DRAW_TILE_OFFSET = 20;
static constexpr int PLAYERS_NUM = 4;
static constexpr int DISCARD_TILE_WIDTH = 80;
static constexpr int DISCARD_TILE_HEIGHT = 116;
static constexpr float FRONT_ORIENTATION = 0.0f;
static constexpr float RIGHT_ORIENTATION = 270.0f;
static constexpr float TOP_ORIENTATION = 180.0f;
static constexpr float LEFT_ORIENTATION = 90.0f;
static constexpr Vector2 FRONT_DISCARD_PILE = { 700,545 };
static constexpr Vector2 RIGHT_DISCARD_PILE = { 1280,720 };
static constexpr Vector2 TOP_DISCARD_PILE = { 1180,400 };
static constexpr Vector2 LEFT_DISCARD_PILE = { 600,240 };
static constexpr int TILES_IN_ROW = 6;
static constexpr Vector2 TILES_COUNTER_POSITION = { 700,480 };
static constexpr int TILES_COUNTER_SIZE = 50;
static constexpr int VALUES_IN_SUIT = 9;

namespace PonButton {
	static constexpr  int X = 1700;
	static constexpr  int Y = 700;
	static constexpr  int WIDTH = 100;
	static constexpr  int HEIGHT = 50;
	static constexpr  int SIZE = 700;
	static constexpr  int FONT_SIZE = 20;
}

namespace SkipButton {
	static constexpr  int X = 1550;
	static constexpr  int Y = 700;
	static constexpr  int WIDTH = 100;
	static constexpr  int HEIGHT = 50;
	static constexpr  int SIZE = 700;
	static constexpr  int FONT_SIZE = 20;
}

namespace PonOptionsView {
	static constexpr  int X = 560;
	static constexpr  int Y = 700;
	static constexpr  int WIDTH = 380;
	static constexpr  int HEIGHT = 140;
	static constexpr  int OP1_X = PonOptionsView::X + 20;
	static constexpr  int OP1_Y = PonOptionsView::Y + 12;
	static constexpr  int OP1_WIDTH = DISCARD_TILE_WIDTH * 2;
	static constexpr  int OP1_HEIGHT = DISCARD_TILE_HEIGHT;
	static constexpr  int OP2_X = PonOptionsView::X + 40 + 2 * DISCARD_TILE_WIDTH;
	static constexpr  int OP2_Y = PonOptionsView::Y + 12;
	static constexpr  int OP2_WIDTH = DISCARD_TILE_WIDTH * 2;
	static constexpr  int OP2_HEIGHT = DISCARD_TILE_HEIGHT;

}