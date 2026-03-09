#include "TileGraphics.h"
#include "Tile.h"
#include "Hand.h"
#include "Discards.h"
#include "GameTypes.h"
#include "Meld.h"
#include "Kan.h"
#include "Triplet.h"

//HandTilesRenderer------------------------------------------------------------

HandTilesRenderer::HandTilesRenderer(const char* handTilesPath, const char* MeldTilesPath) {
	handTileTextures = LoadTexture(handTilesPath);
	meldTileTextures = LoadTexture(MeldTilesPath);
}


HandTilesRenderer::~HandTilesRenderer(){
	UnloadTexture(handTileTextures);
	UnloadTexture(meldTileTextures);
}

void HandTilesRenderer::drawTileAka(const Tile& tile, Vector2 position) const {
	Rectangle sourceRec = { (AKA_PLACE_IN_FILE - 1) * TILE_WIDTH,
		static_cast<int>(tile.getSuit()) * TILE_HEIGHT,
		TILE_WIDTH, TILE_HEIGHT };
	DrawTextureRec(handTileTextures, sourceRec, position, WHITE);
}

void HandTilesRenderer::drawTile(const Tile& tile, Vector2 position) const{
	if (tile.isAkadora()) {
		drawTileAka(tile,position);
	}
	else {
		Rectangle sourceRec = { (tile.getValue() - 1) * TILE_WIDTH,
			static_cast<int>(tile.getSuit()) * TILE_HEIGHT,
			TILE_WIDTH, TILE_HEIGHT };
		DrawTextureRec(handTileTextures, sourceRec, position, WHITE);
	}
}



void HandTilesRenderer::drawMeldTileAka(const Tile& tile, 
	Vector2 position, float orientation) const
{
	Rectangle sourceRec = { (AKA_PLACE_IN_FILE - 1) * MELD_TILE_WIDTH,
			static_cast<int>(tile.getSuit()) * MELD_TILE_HEIGHT,
			MELD_TILE_WIDTH,MELD_TILE_HEIGHT };
	Rectangle destRec = { position.x,position.y,MELD_TILE_WIDTH,MELD_TILE_HEIGHT };
	DrawTexturePro(meldTileTextures, sourceRec, destRec, { 0,0 }, orientation, WHITE);
}

void HandTilesRenderer::drawMeldTile(const Tile& tile, 
	Vector2 position, float orientation) const{
	if (tile.isAkadora()) {
		drawMeldTileAka(tile, position, orientation);
	}
	else {
		Rectangle sourceRec = { (tile.getValue() - 1) * MELD_TILE_WIDTH,
			static_cast<int>(tile.getSuit()) * MELD_TILE_HEIGHT,
			MELD_TILE_WIDTH, MELD_TILE_HEIGHT };
		Rectangle destRec = { position.x,position.y,MELD_TILE_WIDTH,MELD_TILE_HEIGHT };
		DrawTexturePro(meldTileTextures, sourceRec, destRec, { 0,0 }, orientation, WHITE);
	}
}

void HandTilesRenderer::drawMeldTileBack(Vector2 position) const
{
	Rectangle sourceRec = { (BACK_COL_IN_FILE - 1) * MELD_TILE_WIDTH,
		(BACK_ROW_IN_FILE - 1) * MELD_TILE_HEIGHT, MELD_TILE_WIDTH, MELD_TILE_HEIGHT };
	Rectangle destRec = { position.x,position.y,MELD_TILE_WIDTH,MELD_TILE_HEIGHT };
	DrawTexturePro(meldTileTextures, sourceRec, destRec, { 0,0 }, STRAIGHT_ORIENTATION, WHITE);
}

void HandTilesRenderer::drawPon(const Meld& meld, Vector2 position) const {
	float leaningTileY = position.y + MELD_TILE_HEIGHT;
	switch (meld.getTileMarker()) {
	case (TileMarker::LEFT):
		drawMeldTile(meld[0], { position.x,leaningTileY }
		, RIGHT_ORIENTATION);
		drawMeldTile(meld[1], { position.x + MELD_TILE_HEIGHT, position.y }
		, STRAIGHT_ORIENTATION);
		drawMeldTile(meld[2], { position.x + MELD_TILE_WIDTH + MELD_TILE_HEIGHT, position.y }
		, STRAIGHT_ORIENTATION);
		break;
	case (TileMarker::MIDDLE):
		drawMeldTile(meld[1], position, STRAIGHT_ORIENTATION);
		drawMeldTile(meld[0], { position.x + MELD_TILE_WIDTH,leaningTileY }, RIGHT_ORIENTATION);
		drawMeldTile(meld[2], { position.x + MELD_TILE_WIDTH + MELD_TILE_HEIGHT, position.y }
		, STRAIGHT_ORIENTATION);
		break;
	case (TileMarker::RIGHT):
		drawMeldTile(meld[1], position, STRAIGHT_ORIENTATION);
		drawMeldTile(meld[2], { position.x + MELD_TILE_WIDTH,position.y }
		, STRAIGHT_ORIENTATION);
		drawMeldTile(meld[0], { position.x + 2 * MELD_TILE_WIDTH,leaningTileY },
			RIGHT_ORIENTATION);
		break;
	}
}

void HandTilesRenderer::drawChi(const Meld& meld, Vector2 position) const
{
	drawPon(meld, position);
}

void HandTilesRenderer::drawAnkan(const Meld& meld, Vector2 position) const
{
	drawMeldTileBack(position);
	drawMeldTile(meld[0], { position.x + 1 * MELD_TILE_WIDTH,position.y }, STRAIGHT_ORIENTATION);
	drawMeldTile(meld[1], { position.x + 2 * MELD_TILE_WIDTH,position.y }, STRAIGHT_ORIENTATION);
	drawMeldTileBack({ position.x + 3 * MELD_TILE_WIDTH, position.y});
}

void HandTilesRenderer::drawDaiminkan(const Meld& meld, Vector2 position) const
{
	switch (meld.getTileMarker()) {
	case (TileMarker::LEFT): {
		Pon newPon(meld[0], meld[1], meld[2], TileMarker::LEFT);
		drawPon(newPon, position);
		drawMeldTile(meld[3], { position.x + TRIPLET_WIDTH,position.y }, STRAIGHT_ORIENTATION);
		break;
	}
	case (TileMarker::MIDDLE): {
		Pon newPon(meld[0], meld[1], meld[2], TileMarker::MIDDLE);
		drawPon(newPon, position);
		drawMeldTile(meld[3], { position.x + TRIPLET_WIDTH,position.y }, STRAIGHT_ORIENTATION);
		break;
	}
	case (TileMarker::RIGHT): {
		Pon newPon(meld[0], meld[1], meld[2], TileMarker::RIGHT);
		drawPon(newPon, { position.x + MELD_TILE_WIDTH, position.y });
		drawMeldTile(meld[3], position, STRAIGHT_ORIENTATION);
		break;
	}
	}
}

void HandTilesRenderer::drawShouminkan(const Meld& meld, Vector2 position) const
{
	float addedTileY = position.y + MELD_TILE_HEIGHT - MELD_TILE_WIDTH;
	switch (meld.getTileMarker()) {
	case (TileMarker::LEFT): {
		Pon newPon(meld[1], meld[2], meld[3], TileMarker::LEFT);
		drawPon(newPon, position);
		drawMeldTile(meld[0], {position.x, addedTileY }, RIGHT_ORIENTATION);
		break;
	}
	case (TileMarker::MIDDLE): {
		Pon newPon(meld[1], meld[2], meld[3], TileMarker::MIDDLE);
		drawPon(newPon, position);
		drawMeldTile(meld[0], { position.x + MELD_TILE_WIDTH,addedTileY }, RIGHT_ORIENTATION);
		break;
	}
	case (TileMarker::RIGHT): {
		Pon newPon(meld[1], meld[2], meld[3], TileMarker::RIGHT);
		drawPon(newPon,position);
		drawMeldTile(meld[0], {position.x + 2 * MELD_TILE_WIDTH, addedTileY }, RIGHT_ORIENTATION);
		break;
	}
	}
}

void HandTilesRenderer::drawMeld(const Meld& meld, Vector2 position) const
{
	//offsets to align melds with 	
	switch (meld.getMeldType()) {
	case(MeldType::PON):
		drawPon(meld, {position.x + PON_OFFSET, position.y});
		break;
	case(MeldType::CHI):
		drawChi(meld, { position.x + CHI_OFFSET, position.y });
		break;
	case(MeldType::ANKAN):
		drawAnkan(meld, { position.x + ANKAN_OFFSET, position.y });
		break;
	case(MeldType::DAIMINKAN):
		drawDaiminkan(meld, position);
		break;
	case(MeldType::SHOUMINKAN):
		drawShouminkan(meld, { position.x + SHOUMINKAN_OFFSET, position.y });
		break;
	}
}




void HandTilesRenderer::draw(const Hand& hand) const {
	//draw hand tiles
	int size = hand.freeTilesNum();
	if (hand.legalHandSize() < MAX_HAND_SIZE) {
		for (int i = 0; i < hand.freeTilesNum(); i++) {
			drawTile(hand[i],
				{ POSITION.x + (i * TILE_WIDTH),
				POSITION.y });
		}
	}
	else if (hand.legalHandSize() == MAX_HAND_SIZE) {
		for (int i = 0; i < hand.freeTilesNum() - 1; i++) {
			drawTile(hand[i],
				{ POSITION.x + (i * TILE_WIDTH),
				POSITION.y });
		}
		drawTile(hand.lastTile(), { POSITION.x + (TILE_WIDTH * (MAX_HAND_SIZE - 1))
			+ DRAW_TILE_OFFSET,POSITION.y });
	}
	//draw hand melds
	float currentY = MELDS_POS.y;
	for(const auto& meld : hand.getMelds()){
		drawMeld(*meld, { MELDS_POS.x,currentY });
		//to align heights with shouminkan
		if (meld->getMeldType() == MeldType::SHOUMINKAN) {
			currentY -= 2 * MELD_TILE_WIDTH;
		}
		else {
			currentY -= MELD_TILE_HEIGHT;
		}

	}

}

int HandTilesRenderer::getTileIndexFromPosition(Vector2 position){
	if (position.x > POSITION.x + (TILE_WIDTH * (MAX_HAND_SIZE) + DRAW_TILE_OFFSET)
		|| position.x < POSITION.x) {
		return -1;
	}
	if (position.x > POSITION.x + (TILE_WIDTH * (HAND_SIZE)) &&
		position.x < POSITION.x + (TILE_WIDTH * (HAND_SIZE)) + DRAW_TILE_OFFSET) {
		return -1;
	}
	if (position.y > POSITION.y + TILE_HEIGHT || position.y < POSITION.y) {
		return -1;
	}
	if (position.x > POSITION.x + (TILE_WIDTH * (HAND_SIZE))) {
		return (HAND_SIZE);
	}
	return static_cast<int>((position.x - POSITION.x) / TILE_WIDTH);
}











//DiscardTilesRenderer------------------------------------------------------------

DiscardTilesRenderer::DiscardTilesRenderer(const char* path) {
	textures = LoadTexture(path);
}


DiscardTilesRenderer::~DiscardTilesRenderer() {
	UnloadTexture(textures);
}

void DiscardTilesRenderer::drawTileAka(const Tile& tile, Vector2 position,
	float orientation) const{
	Rectangle sourceRec = { (AKA_PLACE_IN_FILE - 1) * TILE_WIDTH,
		static_cast<int>(tile.getSuit()) * TILE_HEIGHT,
		TILE_WIDTH,TILE_HEIGHT };
	Rectangle destRec = { position.x,position.y,TILE_WIDTH,TILE_HEIGHT };
	DrawTexturePro(textures, sourceRec, destRec, { 0,0 }, orientation, WHITE);
}

void DiscardTilesRenderer::drawTile(const Tile& tile, Vector2 position,
	float orientation) const{
	if (tile.isAkadora()) {
		drawTileAka(tile, position,orientation);
	}
	Rectangle sourceRec = { (tile.getValue() - 1) * TILE_WIDTH,
		static_cast<int>(tile.getSuit()) * TILE_HEIGHT,
		TILE_WIDTH, TILE_HEIGHT };
	Rectangle destRec = { position.x,position.y,TILE_WIDTH,TILE_HEIGHT };
	DrawTexturePro(textures, sourceRec, destRec, { 0,0 }, orientation, WHITE);
}

void DiscardTilesRenderer::drawDiscardsMine(const Discards& discards) const{
	int i = 0;
	for (const auto& tile : discards) {
		drawTile(tile, { MY_PILE_POS.x +
		((i % TILES_IN_ROW) * TILE_WIDTH) ,MY_PILE_POS.y +
			(i / TILES_IN_ROW) * TILE_HEIGHT }, FRONT_ORIENTATION);
		i++;
	}
}

void DiscardTilesRenderer::drawDiscardsTop(const Discards& discards) const{
	int i = 0;
	for (const auto& tile : discards) {
		drawTile(tile, { TOP_PILE_POS.x -
		((i % TILES_IN_ROW) * TILE_WIDTH) ,TOP_PILE_POS.y -
			(i / TILES_IN_ROW) * TILE_HEIGHT }, TOP_ORIENTATION);
		i++;
	}
}
void DiscardTilesRenderer::drawDiscardsRight(const Discards& discards) const{
	int i = 0;
	for (const auto& tile : discards) {
		drawTile(tile, { RIGHT_PILE_POS.x +
		((i / TILES_IN_ROW) * TILE_HEIGHT) ,RIGHT_PILE_POS.y -
			(i % TILES_IN_ROW) * TILE_WIDTH }, RIGHT_ORIENTATION);
		i++;
	}
}
void DiscardTilesRenderer::drawDiscardsLeft(const Discards& discards) const{
	int i = 0;
	for (const auto& tile : discards) {
		drawTile(tile, { LEFT_PILE_POS.x -
		((i / TILES_IN_ROW) * TILE_HEIGHT) ,LEFT_PILE_POS.y +
			(i % TILES_IN_ROW) * TILE_WIDTH }, LEFT_ORIENTATION);
		i++;
	}
}



void DiscardTilesRenderer::draw(const Discards& discards
	, Wind playerWind, Wind discardsWind) const {

	//calculates a number based on given player wind relative to given discard pile wind.
	// 0 = me, 1 = left pile, 2 = top pile, 3 = right pile.
	int relativePosition = (static_cast<int>(playerWind)
		- static_cast<int>(discardsWind) + PLAYERS_NUM) % PLAYERS_NUM;

	switch (relativePosition) {
	case RELATIVE_POSITION_MINE:
		drawDiscardsMine(discards);
		break;
	case  RELATIVE_POSITION_LEFT:
		drawDiscardsLeft(discards);
		break;

	case RELATIVE_POSITION_TOP:
		drawDiscardsTop(discards);
		break;

	case RELATIVE_POSITION_RIGHT:
		drawDiscardsRight(discards);
		break;
	}
}