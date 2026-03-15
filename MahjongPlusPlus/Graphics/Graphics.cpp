#include "Graphics/Graphics.h"
#include "Graphics/Paths.h"
#include "Graphics/TileGraphics.h"
#include "Core/Player.h"
#include "Core/GameTypes.h"

Graphics::Graphics() = default;
Graphics::~Graphics() = default;


void Graphics::init() {
	background = LoadTexture("assets/background.jpg");
	handTilesRenderer = std::make_unique<HandTilesRenderer>(AssetPaths::handTiles,
		AssetPaths::meldTiles,AssetPaths::meldTilesR);
	discardTilesRenderer = 
		std::make_unique<DiscardTilesRenderer>(	AssetPaths::discardTiles,
			AssetPaths::discardTilesL,
			AssetPaths::discardTilesU,
			AssetPaths::discardTilesR);
}

void Graphics::drawBackground() {
	Rectangle sourceRec = { 0.0f,0.0f,
		static_cast<float>(background.width),static_cast<float>(background.height) };
	Rectangle destRec = { 0.0f,0.0f,
	static_cast<float>(SCREEN_WIDTH),static_cast<float>(SCREEN_HEIGHT)};
	DrawTexturePro(background, sourceRec, destRec, { 0.0f,0.0f }, 0.0f, GRAY);
}

void Graphics::clean() {
	UnloadTexture(background);
}

void Graphics::drawTilesLeft(int tilesLeft) {
	std::string str = "Tiles left: " + std::to_string(tilesLeft);
	DrawText(str.c_str(), TILES_COUNTER_POSITION.x, TILES_COUNTER_POSITION.y,
		TILES_COUNTER_SIZE, RED);
}

void Graphics::drawTileHitBox(const Hand& hand, const HandTilesLayout& layout) const
{
	handTilesRenderer->drawHitBoxes(hand,layout);
	Vector2 mousePos = GetMousePosition();
	DrawCircleV(mousePos, 5.0f, RED);
}

void Graphics::drawWinds(Wind perspectiveWind) const
{
	std::string WINDSTR[4] = {"E","S","W","N"};
	int playerWind = static_cast<int>(perspectiveWind);
	DrawText(WINDSTR[playerWind].c_str(), MY_WIND_POS.x, MY_WIND_POS.y, 100, RED);
	DrawText(WINDSTR[(playerWind + 1) % 4].c_str(), RIGHT_WIND_POS.x, RIGHT_WIND_POS.y, 100, BLACK);
	DrawText(WINDSTR[(playerWind + 2) % 4].c_str(), TOP_WIND_POS.x, TOP_WIND_POS.y, 100, BLACK);
	DrawText(WINDSTR[(playerWind + 3) % 4].c_str(), LEFT_WIND_POS.x, LEFT_WIND_POS.y, 100, BLACK);
}


void Graphics::drawHand(const Hand& hand,
	const HandTilesLayout& handTilesLayout, const MeldsLayout& meldsLayout) const {
	handTilesRenderer->draw(hand, handTilesLayout, meldsLayout);
}

void Graphics::drawDiscards(const std::array<std::unique_ptr<Player>, Constants::PLAYERS_NUM>& players,
	std::array<PlayerDiscardsLayout, Constants::PLAYERS_NUM> layouts) const {
	for (int i = 0; i < Constants::PLAYERS_NUM; i++) {
		discardTilesRenderer->draw(players[i]->getDiscards(),layouts[i]);
	}
}






