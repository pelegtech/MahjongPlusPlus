#include "Graphics/Graphics.h"
#include "Graphics/Paths.h"
#include "Graphics/TileGraphics.h"
#include "Core/Player.h"
#include "Core/GameTypes.h"
#include "Layouts\TileLayouts.h"
#include "Core/Wall.h"

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
	
	deadWallRenderer = std::make_unique<DeadWallRenderer>(AssetPaths::deadWallTiles);
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

void Graphics::drawTileHitBox(const HandTilesLayout& layout) const
{
	handTilesRenderer->drawHitBoxes(layout);
	Vector2 mousePos = GetMousePosition();
	DrawCircleV(mousePos, 5.0f, RED);
}

void Graphics::drawWinds(Wind perspectiveWind) const
{
	static const char* WINDSTR[4] = {"E","S","W","N"};
	Vector2 POSITIONS[4] = { MY_WIND_POS,RIGHT_WIND_POS,TOP_WIND_POS, LEFT_WIND_POS };
	int playerWind = static_cast<int>(perspectiveWind);
	for(int i = 0; i < Constants::PLAYERS_NUM; i++){
		DrawText(WINDSTR[(playerWind + i) % 4], POSITIONS[i].x, POSITIONS[i].y, WIND_INDICATOR_SIZE, (((playerWind + i) % 4) == 0) ? RED : BLACK);
	}
}

void Graphics::drawDiscardsHitboxes(const GameDiscardsLayout& layout) const
{
	layout.drawHitBoxes();
}

void Graphics::highlightLastDiscard(const PlayerDiscardsLayout layout) const
{
	discardTilesRenderer->highlightCurrentDiscard(layout);
}

DiscardTilesRenderer& Graphics::getDiscardRenderer() const
{
	return *discardTilesRenderer;
}

void Graphics::drawDeadWall(const Wall& wall, const DeadWallLayout& layout) const
{
	deadWallRenderer->draw(wall, layout);
}

void Graphics::highlightDorasDiscards(const std::array<std::unique_ptr<Player>, Constants::PLAYERS_NUM>& players, std::array<PlayerDiscardsLayout, Constants::PLAYERS_NUM> layouts, const Wall& wall)
{
	for (int i = 0; i < Constants::PLAYERS_NUM; i++) {
		discardTilesRenderer->highlightDora(players[i]->getDiscards(), layouts[i], wall);
	}
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






