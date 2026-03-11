#include "Layout.h"
#include "Hand.h"


HandTilesLayout::HandTilesLayout(const Hand& hand): size(hand.freeTilesNum())
{
	for (int i = 0; i < size; i++) {
		recs[i] = getTileRec(hand,i);
	}
}

Rectangle HandTilesLayout::getTileRec(const Hand& hand, int index)
{
	if (index >= hand.freeTilesNum() || index < 0) {
		throw Hand::illegalAcess();
	}
	if (index == (hand.freeTilesNum() - 1)) {
		Rectangle res = { POSITION.x + (index)* WIDTH + DRAW_TILE_OFFSET,
			POSITION.y, WIDTH,HEIGHT };
		return res;
	}
	else {
		Rectangle res = { POSITION.x + (index)* WIDTH,
			POSITION.y, WIDTH, HEIGHT };
		return res;
	}
}



MeldLayout::MeldLayout(const Meld& meld, Vector2 position): recs{0}, size(0)
{
	switch (meld.getMeldType()) {
	case (MeldType::PON):
		ponLayout(meld, position);
		break;
	case (MeldType::CHI):
		chiLayout(meld, position);
		break;
	case (MeldType::ANKAN):
		ankanLayout(meld, position);
		break;
	case (MeldType::DAIMINKAN):
		daiminkanLayout(meld, position);
		break;
	case (MeldType::SHOUMINKAN):
		shouminkanLayout(meld, position);
		break;
	}
}

void MeldLayout::ponLayout(const Meld& meld, Vector2 position) {
	size = TRIPLET_TILE_NUM;
	float leaningTileY = position.y + TILE_HEIGHT - TILE_WIDTH;
	switch (meld.getTileMarker()) {
	case (TileMarker::LEFT):
		recs[0] = {  position.x ,leaningTileY, TILE_HEIGHT, TILE_WIDTH };
		recs[1] = {	position.x + TILE_HEIGHT, position.y, TILE_WIDTH, TILE_HEIGHT };
		recs[2] = { position.x + TILE_HEIGHT + TILE_WIDTH, position.y, TILE_WIDTH, TILE_HEIGHT };


		break;
	case (TileMarker::MIDDLE):
		recs[0] = { position.x ,position.y, TILE_WIDTH, TILE_HEIGHT };
		recs[1] = { position.x + TILE_WIDTH,leaningTileY, TILE_HEIGHT, TILE_WIDTH };
		recs[2] = { position.x + TILE_WIDTH + TILE_HEIGHT, position.y, TILE_WIDTH, TILE_HEIGHT };
		break;
	case (TileMarker::RIGHT):


		recs[0] = { position.x ,position.y, TILE_WIDTH, TILE_HEIGHT };
		recs[1] = { position.x + TILE_WIDTH,position.y, TILE_WIDTH, TILE_HEIGHT };
		recs[2] = { position.x + 2 * TILE_WIDTH,leaningTileY, TILE_HEIGHT, TILE_WIDTH };
		break;
	}
}

void MeldLayout::chiLayout(const Meld& meld, Vector2 position)
{
	ponLayout(meld, position);
}

void MeldLayout::ankanLayout(const Meld& meld, Vector2 position)
{
	size = KAN_TILE_NUM;
	for (int i = 0; i < size; i++) {
		recs[i] = { position.x + i * TILE_WIDTH,position.y,TILE_WIDTH,TILE_HEIGHT };
	}
}

void MeldLayout::daiminkanLayout(const Meld& meld, Vector2 position)
{
	switch (meld.getTileMarker()) {
	case (TileMarker::LEFT): {
		ponLayout(meld, position);
		size = KAN_TILE_NUM;
		recs[3] = { position.x + TRIPLET_WIDTH,position.y, TILE_WIDTH,TILE_HEIGHT };
		break;

	}
	case (TileMarker::MIDDLE): {
		ponLayout(meld, position);
		size = KAN_TILE_NUM;
		recs[3] = { position.x + TRIPLET_WIDTH,position.y, TILE_WIDTH,TILE_HEIGHT };
		break;
	}
	case (TileMarker::RIGHT): {
		ponLayout(meld, { position.x + TILE_WIDTH, position.y });
		size = KAN_TILE_NUM;
		recs[3] = { position.x ,position.y, TILE_WIDTH,TILE_HEIGHT };
		break;

	}
	}
}

void MeldLayout::shouminkanLayout(const Meld& meld, Vector2 position)
{
	float addedTileY = position.y + TILE_HEIGHT - 2 * TILE_WIDTH;
	switch (meld.getTileMarker()) {
	case (TileMarker::LEFT): {
		ponLayout(meld, position);
		size = KAN_TILE_NUM;
		recs[3] = { position.x, addedTileY , TILE_HEIGHT,TILE_WIDTH };
		break;

	}
	case (TileMarker::MIDDLE): {
		ponLayout(meld, position);
		size = KAN_TILE_NUM;
		recs[3] = { position.x + TILE_WIDTH,addedTileY, TILE_HEIGHT,TILE_WIDTH };
		break;
	}
	case (TileMarker::RIGHT): {
		ponLayout(meld, position);
		size = KAN_TILE_NUM;
		recs[3] = { position.x + 2 * TILE_WIDTH, addedTileY,TILE_HEIGHT,TILE_WIDTH };
		break;
	}
	}
}

MeldsLayout::MeldsLayout(const std::vector<std::unique_ptr<Meld>>& melds): size(melds.size())
{
	if (melds.size() > MAX_MELD_NUM) {
		throw Hand::illegalAcess();
	}
	float currentX = MELDS_POS.x;
	int i = 0;
	for (const auto& meld : melds) {
		float currentMeldWidth = 0;

		if (meld->getMeldType() == MeldType::PON || meld->getMeldType() == MeldType::CHI
			|| meld->getMeldType() == MeldType::SHOUMINKAN) {
			currentMeldWidth = TRIPLET_WIDTH;
		}
		else if (meld->getMeldType() == MeldType::DAIMINKAN) {
			currentMeldWidth = DAIMINKAN_WIDTH;
		}
		else if (meld->getMeldType() == MeldType::ANKAN) {
			currentMeldWidth = ANKAN_WIDTH;
		}
		currentX -= currentMeldWidth;
		layouts[i++] = MeldLayout( (*meld), { currentX,MELDS_POS.y });
		currentX -= MELD_SPACE;
	}
}
