#include "TileGraphics.h"
#include "Tile.h"
#include "Hand.h"
#include "Discards.h"
#include "GameTypes.h"
#include "Meld.h"
#include "Kan.h"
#include "Triplet.h"

//HandTilesRenderer------------------------------------------------------------

HandTilesRenderer::HandTilesRenderer(const char* handTilesPath, const char* meldTilesPath,
	const char* meldTilesRPath) {
	handTileTextures = LoadTexture(handTilesPath);
	meldTileTextures = LoadTexture(meldTilesPath);
	meldTileTexturesR = LoadTexture(meldTilesRPath);
}


HandTilesRenderer::~HandTilesRenderer(){
	UnloadTexture(handTileTextures);
	UnloadTexture(meldTileTextures);
	UnloadTexture(meldTileTexturesR);
}

void HandTilesRenderer::drawTileAka(const Tile& tile,Rectangle layout) const {
	Rectangle sourceRec = { (AKA_PLACE_IN_FILE - 1) * TILE_WIDTH_SRC,
		static_cast<int>(tile.getSuit()) * TILE_HEIGHT_SRC,
		TILE_WIDTH_SRC, TILE_HEIGHT_SRC };
	DrawTexturePro(handTileTextures, sourceRec, layout, { 0,0 }, 0.0f, WHITE);
}

void HandTilesRenderer::drawTile(const Tile& tile,Rectangle layout) const{
	if (tile.isAkadora()) {
		drawTileAka(tile,layout);
	}
	else {
		Rectangle sourceRec = { (tile.getValue() - 1) * TILE_WIDTH_SRC,
			static_cast<int>(tile.getSuit()) * TILE_HEIGHT_SRC,
			TILE_WIDTH_SRC,  TILE_HEIGHT_SRC };
		DrawTexturePro(handTileTextures, sourceRec, layout, { 0,0 }, 0.0f, WHITE);
	}
}



void HandTilesRenderer::drawMeldTileAka(const Tile& tile, Rectangle layout) const
{
	Rectangle sourceRec = { (AKA_PLACE_IN_FILE - 1) * MELD_TILE_WIDTH_SRC,
			static_cast<int>(tile.getSuit()) * MELD_TILE_HEIGHT_SRC,
			MELD_TILE_WIDTH_SRC,MELD_TILE_HEIGHT_SRC };
	DrawTexturePro(meldTileTextures, sourceRec, layout, { 0,0 }, 0.0f, WHITE);
}

void HandTilesRenderer::drawMeldTile(const Tile& tile, Rectangle layout) const{
	if (tile.isAkadora()) {
		drawMeldTileAka(tile,layout);
	}
	else {
		Rectangle sourceRec = { (tile.getValue() - 1) * MELD_TILE_WIDTH_SRC,
			static_cast<int>(tile.getSuit()) * MELD_TILE_HEIGHT_SRC,
			MELD_TILE_WIDTH_SRC, MELD_TILE_HEIGHT_SRC };
		DrawTexturePro(meldTileTextures, sourceRec, layout, { 0,0 }, 0.0f, WHITE);
	}
}

void HandTilesRenderer::drawMeldTileBack(Rectangle layout) const
{
	Rectangle sourceRec = { (BACK_COL_IN_FILE - 1) * MELD_TILE_WIDTH_SRC,
		(BACK_ROW_IN_FILE - 1) * MELD_TILE_HEIGHT_SRC, MELD_TILE_WIDTH_SRC, MELD_TILE_HEIGHT_SRC };
	DrawTexturePro(meldTileTextures, sourceRec, layout, { 0,0 },0.0f, WHITE);
}

void HandTilesRenderer::drawMeldTileAkaRight(const Tile& tile, Rectangle layout) const
{
	Rectangle sourceRec = { static_cast<int>(tile.getSuit()) * MELD_TILE_HEIGHT_SRC
		,(AKA_PLACE_IN_FILE - 1)* MELD_TILE_WIDTH_SRC,MELD_TILE_HEIGHT_SRC, MELD_TILE_WIDTH_SRC };
	DrawTexturePro(meldTileTexturesR, sourceRec, layout, { 0,0 }, 0.0f, WHITE);
}

void HandTilesRenderer::drawMeldTileRight(const Tile& tile, Rectangle layout) const
{
	if (tile.isAkadora()) {
		drawMeldTileAkaRight(tile, layout);
	}
	else {
		Rectangle sourceRec = { static_cast<int>(tile.getSuit()) * MELD_TILE_HEIGHT_SRC
			,(tile.getValue() - 1)* MELD_TILE_WIDTH_SRC,MELD_TILE_HEIGHT_SRC, MELD_TILE_WIDTH_SRC };
		DrawTexturePro(meldTileTexturesR, sourceRec, layout, { 0,0 }, 0.0f, WHITE);
	}
}

void HandTilesRenderer::drawPon(const Meld& meld,const MeldLayout& layout) const {
	switch (meld.getTileMarker()) {
	case (TileMarker::LEFT):
		drawMeldTileRight(meld[0], layout.recs[0]);
		drawMeldTile(meld[1], layout.recs[1]);
		drawMeldTile(meld[2], layout.recs[2]);
		break;
	case (TileMarker::MIDDLE):
		drawMeldTile(meld[1], layout.recs[0]);
		drawMeldTileRight(meld[0], layout.recs[1]);
		drawMeldTile(meld[2], layout.recs[2]);
		break;
	case (TileMarker::RIGHT):
		drawMeldTile(meld[1], layout.recs[0]);
		drawMeldTile(meld[2], layout.recs[1]);
		drawMeldTileRight(meld[0], layout.recs[2]);
		break;
	}
}

void HandTilesRenderer::drawChi(const Meld& meld, const MeldLayout& layout) const
{
	drawPon(meld, layout);
}

void HandTilesRenderer::drawAnkan(const Meld& meld, const MeldLayout& layout) const
{
	drawMeldTileBack(layout.recs[0]);
	drawMeldTile(meld[0],layout.recs[1]);
	drawMeldTile(meld[1], layout.recs[2]);
	drawMeldTileBack(layout.recs[3]);
}

void HandTilesRenderer::drawDaiminkan(const Meld& meld, const MeldLayout& layout) const
{
	Pon newPon(meld[0], meld[1], meld[2], meld.getTileMarker());
	drawPon(newPon, layout);
	drawMeldTile(meld[3], layout.recs[3]);
}

void HandTilesRenderer::drawShouminkan(const Meld& meld,const MeldLayout& layout) const
{
	Pon newPon(meld[0], meld[1], meld[2], meld.getTileMarker());
	drawPon(newPon, layout);
	drawMeldTileRight(meld[3], layout.recs[3]);
}

void HandTilesRenderer::drawMeld(const Meld& meld,const MeldLayout& layout) const
{
	switch (meld.getMeldType()) {
	case(MeldType::PON):
		drawPon(meld,layout);
		break;
	case(MeldType::CHI):
		drawChi(meld, layout);
		break;
	case(MeldType::ANKAN):
		drawAnkan(meld, layout);
		break;
	case(MeldType::DAIMINKAN):
		drawDaiminkan(meld, layout);
		break;
	case(MeldType::SHOUMINKAN):
		drawShouminkan(meld, layout);
		break;
	}
}




void HandTilesRenderer::draw(const Hand& hand, const HandTilesLayout& handTilesLayout,
	const MeldsLayout& meldsLayout) const {
	//draw hand tiles
	for (int i = 0; i < hand.freeTilesNum(); i++) {
		drawTile(hand[i], handTilesLayout.recs[i]);
			
	}
	//draw meld tiles
	for (int i = 0; i < hand.getMelds().size(); i++) {
		drawMeld(*(hand.getMelds()[i]),meldsLayout.layouts[i]);
	}
}

void HandTilesRenderer::drawHitBoxes(const Hand& hand, const HandTilesLayout& handTilesLayout) const
{
	for (int i = 0; i < hand.freeTilesNum();i++) {
		DrawRectangleLinesEx(handTilesLayout.recs[i], 4.0f, GOLD);
	}
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
	else {
		Rectangle sourceRec = { (tile.getValue() - 1) * TILE_WIDTH,
			static_cast<int>(tile.getSuit()) * TILE_HEIGHT,
			TILE_WIDTH, TILE_HEIGHT };
		Rectangle destRec = { position.x,position.y,TILE_WIDTH,TILE_HEIGHT };
		DrawTexturePro(textures, sourceRec, destRec, { 0,0 }, orientation, WHITE);
	}
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