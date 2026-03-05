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
	Rectangle sourceRec = { (tile.getValue() - 1) * TILE_WIDTH,
		static_cast<int>(tile.getSuit()) * TILE_HEIGHT,
		TILE_WIDTH, TILE_HEIGHT};
	DrawTextureRec(handTiles, sourceRec, position, WHITE);
}
void Graphics::drawHand(const Hand& hand) {
	int size = hand.tilesNum();
	if (hand.legalHandSize() < 14) {
		for (int i = 0; i < hand.tilesNum(); i++) {
			drawHandTile(hand[i],
				{ HAND_POSITION.x + (i * TILE_WIDTH),
				HAND_POSITION.y});
		}
	}
	else if (hand.legalHandSize() == 14) {
		for (int i = 0; i < hand.tilesNum() - 1; i++) {
			drawHandTile(hand[i],
				{ HAND_POSITION.x + (i * TILE_WIDTH),
				HAND_POSITION.y});
		}
		drawHandTile(hand.lastTile(), { HAND_POSITION.x + (TILE_WIDTH * (HAND_SIZE - 1)) 
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
	if (position.x > HAND_POSITION.x + (TILE_WIDTH * (HAND_SIZE) + DRAW_TILE_OFFSET)
		|| position.x < HAND_POSITION.x) {
		return -1;
	}
	if (position.x > HAND_POSITION.x + (TILE_WIDTH * (HAND_SIZE - 1)) && 
		position.x < HAND_POSITION.x + (TILE_WIDTH * (HAND_SIZE - 1)) + DRAW_TILE_OFFSET){
		return -1;
	}
	if (position.y > HAND_POSITION.y + TILE_HEIGHT || position.y < HAND_POSITION.y){
		return -1;
	}
	if (position.x > HAND_POSITION.x + (TILE_WIDTH * (HAND_SIZE - 1))) {
		return (HAND_SIZE - 1);
	} 
	return static_cast<int>((position.x - HAND_POSITION.x) / TILE_WIDTH);
}