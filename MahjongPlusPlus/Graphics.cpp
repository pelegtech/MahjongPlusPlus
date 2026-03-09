#include "Graphics.h"

void Graphics::init() {
	background = LoadTexture("assets/background.jpg");
	handTilesRenderer = std::make_unique<HandTilesRenderer>(AssetPaths::handTiles,
		AssetPaths::meldTiles);
	discardTilesRenderer = std::make_unique<DiscardTilesRenderer>(AssetPaths::discardTiles);
	buttons = LoadTexture("assets/buttons.png");
}

void Graphics::drawBackground() {
	Rectangle sourceRec = { 0.0f,0.0f,
		static_cast<float>(background.width),static_cast<float>(background.height) };
	Rectangle destRec = { 0.0f,0.0f,
	static_cast<float>(SCREEN_WIDTH),static_cast<float>(SCREEN_HEIGHT)};
	DrawTexturePro(background, sourceRec, destRec, { 0.0f,0.0f }, 0.0f, WHITE);
}

void Graphics::clean() {
	UnloadTexture(background);
	UnloadTexture(buttons);
}

void Graphics::drawTilesLeft(int tilesLeft) {
	std::string str = "Tiles left: " + std::to_string(tilesLeft);
	DrawText(str.c_str(), TILES_COUNTER_POSITION.x, TILES_COUNTER_POSITION.y,
		TILES_COUNTER_SIZE, BLACK);
}

void Graphics::drawHand(const Hand& hand) const {
	handTilesRenderer->draw(hand);
}

void Graphics::drawDiscards(const Player& perspectivePayer, const Player& p2, const Player& p3,
	const Player& p4) const {
	discardTilesRenderer->draw(perspectivePayer.getDiscards(), perspectivePayer.getWind()
		, perspectivePayer.getWind());
	discardTilesRenderer->draw(p2.getDiscards(), perspectivePayer.getWind(), p2.getWind());
	discardTilesRenderer->draw(p3.getDiscards(), perspectivePayer.getWind(), p3.getWind());
	discardTilesRenderer->draw(p4.getDiscards(), perspectivePayer.getWind(), p4.getWind());
}






