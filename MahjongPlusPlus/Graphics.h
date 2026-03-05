#pragma once
#include "raylib.h"
#include "Player.h"
#include "Hand.h"
#include "Tile.h"
#include "Discards.h"
#include "GameTypes.h"


class Graphics {
private:
	Texture2D background;
	Texture2D handTiles;
	Texture2D discardTiles;
	Texture2D buttons;
public:
	static constexpr int SCREEN_WIDTH = 1920;
	static constexpr int SCREEN_HEIGHT = 1080;
	static constexpr int TILE_WIDTH = 80;
	static constexpr int TILE_HEIGHT = 129;
	static constexpr int HAND_SIZE = 14;
	static constexpr Vector2 HAND_POSITION = { 340,900 };
	static constexpr int DRAW_TILE_OFFSET = 20;
	


	Graphics() = default;
	void init();
	void drawBackground();
	void drawHandTile(const Tile& tile,Vector2 position);
	void drawHand(const Hand& hand);
	static int getTileIndexFromPosition(Vector2 position);
	/*void drawHand(const Hand& hand);
	void drawDiscardPile(const Discards& discard, Wind playerWind, Wind discardsWind);*/
	void clean();
};