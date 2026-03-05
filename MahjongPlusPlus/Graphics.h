#pragma once
#include "raylib.h"
#include "Player.h"
#include "Hand.h"
#include "Tile.h"
#include "Discards.h"
#include "GameTypes.h"
#include <string>

class Graphics {
private:
	Texture2D background;
	Texture2D handTiles;
	Texture2D discardTiles;
	Texture2D buttons;
public:
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
	


	Graphics() = default;
	void init();
	void drawBackground();
	void drawHandTile(const Tile& tile,Vector2 position);
	void drawHand(const Hand& hand);
	static int getTileIndexFromPosition(Vector2 position);
	void drawDiscardTile(const Tile& tile, Vector2 position,float orienation);
	void drawDiscardPile(const Discards& discards, Wind playerWind, Wind discardsWind);
	void clean();
	void drawTilesLeft(int tilesLeft);
};