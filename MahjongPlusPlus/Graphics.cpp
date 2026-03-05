#include "Graphics.h"

void Graphics::init() {
	background = LoadTexture("assets/background.jpg");
	handTiles = LoadTexture("assets/mjs_tiles.png");
	discardTiles = LoadTexture("assets/discard_tiles.png");
	buttons = LoadTexture("assets/buttons.png");
}
void Graphics::drawBackground() {
	Rectangle sourceRec = { 0.0f,0.0f,
		static_cast<float>(background.width),static_cast<float>(background.height) };
	Rectangle destRec = { 0.0f,0.0f,
	static_cast<float>(SCREEN_WIDTH),static_cast<float>(SCREEN_HEIGHT)};
	DrawTexturePro(background, sourceRec, destRec, { 0.0f,0.0f }, 0.0f, WHITE);
}

void Graphics::drawHandTile(const Tile& tile, Vector2 position) {
	Rectangle sourceRec = { (tile.getValue() - 1) * HAND_TILE_WIDTH,
		static_cast<int>(tile.getSuit()) * HAND_TILE_HEIGHT,
		HAND_TILE_WIDTH, HAND_TILE_HEIGHT};
	DrawTextureRec(handTiles, sourceRec, position, WHITE);
}
void Graphics::drawHand(const Hand& hand) {
	int size = hand.tilesNum();
	if (hand.legalHandSize() < 14) {
		for (int i = 0; i < hand.tilesNum(); i++) {
			drawHandTile(hand[i],
				{ HAND_POSITION.x + (i * HAND_TILE_WIDTH),
				HAND_POSITION.y});
		}
	}
	else if (hand.legalHandSize() == 14) {
		for (int i = 0; i < hand.tilesNum() - 1; i++) {
			drawHandTile(hand[i],
				{ HAND_POSITION.x + (i * HAND_TILE_WIDTH),
				HAND_POSITION.y});
		}
		drawHandTile(hand.lastTile(), { HAND_POSITION.x + (HAND_TILE_WIDTH * (HAND_SIZE - 1)) 
			+ DRAW_TILE_OFFSET,HAND_POSITION.y });
	}
}
void Graphics::clean() {
	UnloadTexture(background);
	UnloadTexture(handTiles);
	UnloadTexture(discardTiles);
	UnloadTexture(buttons);
}

int Graphics::getTileIndexFromPosition(Vector2 position) {
	if (position.x > HAND_POSITION.x + (HAND_TILE_WIDTH * (HAND_SIZE) + DRAW_TILE_OFFSET)
		|| position.x < HAND_POSITION.x) {
		return -1;
	}
	if (position.x > HAND_POSITION.x + (HAND_TILE_WIDTH * (HAND_SIZE - 1)) && 
		position.x < HAND_POSITION.x + (HAND_TILE_WIDTH * (HAND_SIZE - 1)) + DRAW_TILE_OFFSET){
		return -1;
	}
	if (position.y > HAND_POSITION.y + HAND_TILE_HEIGHT || position.y < HAND_POSITION.y){
		return -1;
	}
	if (position.x > HAND_POSITION.x + (HAND_TILE_WIDTH * (HAND_SIZE - 1))) {
		return (HAND_SIZE - 1);
	} 
	return static_cast<int>((position.x - HAND_POSITION.x) / HAND_TILE_WIDTH);
}

void Graphics::drawDiscardTile(const Tile& tile, Vector2 position, float orientation) {
	Rectangle sourceRec = { (tile.getValue() - 1) * DISCARD_TILE_WIDTH,
		static_cast<int>(tile.getSuit()) * DISCARD_TILE_HEIGHT,
		DISCARD_TILE_WIDTH, DISCARD_TILE_HEIGHT };
	Rectangle destRec = { position.x,position.y,DISCARD_TILE_WIDTH,DISCARD_TILE_HEIGHT };
	DrawTexturePro(discardTiles, sourceRec, destRec, { 0,0 }, orientation, WHITE);
}


void Graphics::drawDiscardPile(const Discards& discards, Wind playerWind, Wind discardsWind) {
	int relativePosition = (static_cast<int>(playerWind)
		- static_cast<int>(discardsWind) + PLAYERS_NUM) % PLAYERS_NUM;
	switch (relativePosition) {
	case 0: {
		int i = 0;
		for (const auto& tile : discards) {
			drawDiscardTile(tile, { FRONT_DISCARD_PILE.x +
			((i % TILES_IN_ROW) * DISCARD_TILE_WIDTH) ,FRONT_DISCARD_PILE.y +
				(i / TILES_IN_ROW) * DISCARD_TILE_HEIGHT }, FRONT_ORIENTATION);
			i++;
		}
		break;
	}
	case 1: {
		int i = 0;
		for (const auto& tile : discards) {
			drawDiscardTile(tile, { LEFT_DISCARD_PILE.x -
			((i / TILES_IN_ROW) * DISCARD_TILE_HEIGHT) ,LEFT_DISCARD_PILE.y +
				(i % TILES_IN_ROW) * DISCARD_TILE_WIDTH }, LEFT_ORIENTATION);
			i++;
		}
		break;
	}
	case 2: {
		int i = 0;
		for (const auto& tile : discards) {
			drawDiscardTile(tile, { TOP_DISCARD_PILE.x -
			((i % TILES_IN_ROW) * DISCARD_TILE_WIDTH) ,TOP_DISCARD_PILE.y -
				(i / TILES_IN_ROW) * DISCARD_TILE_HEIGHT }, TOP_ORIENTATION);
			i++;
		}
		break;
	}
	case 3: {
		int i = 0;
		for (const auto& tile : discards) {
			drawDiscardTile(tile, { RIGHT_DISCARD_PILE.x +
			((i / TILES_IN_ROW) * DISCARD_TILE_HEIGHT) ,RIGHT_DISCARD_PILE.y -
				(i % TILES_IN_ROW) * DISCARD_TILE_WIDTH }, RIGHT_ORIENTATION);
			i++;
		}
		break;
	}
	}
}

void Graphics::drawTilesLeft(int tilesLeft) {
	std::string str = "Tiles left: " + std::to_string(tilesLeft);
	DrawText(str.c_str(),TILES_COUNTER_POSITION.x, TILES_COUNTER_POSITION.y,
		TILES_COUNTER_SIZE, BLACK);
}