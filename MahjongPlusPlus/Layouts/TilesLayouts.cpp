#include "Layouts/TilesLayouts.h"
#include "Core/Hand.h"
#include "Core/Meld.h"
#include "Core/Discards.h"
#include "Core/Player.h"

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

PlayerDiscardsLayout::PlayerDiscardsLayout(const Discards& discards, RelativePosition position):recs{0}, size(discards.getSize()),position(position)
{
	size = discards.getSize();
	int posNum = static_cast<int>(position);
	int riichiId = discards.getRiichiId();
	if (riichiId == -1) {
		for (int i = 0; i < size; i++) {
			int row = i / TILES_IN_ROW;
			int col = i % TILES_IN_ROW;
			float currentX = posConsts[posNum].position.x + col * posConsts[posNum].colStep.x + row * posConsts[posNum].rowStep.x;
			float currentY = posConsts[posNum].position.y + col * posConsts[posNum].colStep.y + row * posConsts[posNum].rowStep.y;
			Rectangle current = { currentX, currentY, posConsts[posNum].width,posConsts[posNum].height };
			recs[i] = current;
		}
	}
	else {
		int riichiRow = riichiId / TILES_IN_ROW;
		for (int i = 0; i < size; i++) {
			int row = i / TILES_IN_ROW;
			int col = i % TILES_IN_ROW;
			float currentX = posConsts[posNum].position.x + col * posConsts[posNum].colStep.x + row * posConsts[posNum].rowStep.x;
			float currentY = posConsts[posNum].position.y + col * posConsts[posNum].colStep.y + row * posConsts[posNum].rowStep.y;
			if (i < riichiId || (i > riichiId && row != riichiRow)) {
				Rectangle current = { currentX, currentY, posConsts[posNum].width,posConsts[posNum].height };
				recs[i] = current;
			}
			else if (i > riichiId && (row == riichiRow)) {
				currentX += posConsts[posNum].afterRiichiShift.x;
				currentY += posConsts[posNum].afterRiichiShift.y;
				Rectangle current = { currentX, currentY, posConsts[posNum].width,posConsts[posNum].height };
				recs[i] = current;
			}
			else if (i == riichiId) {
				currentX += posConsts[posNum].riichiOffset.x;
				currentY += posConsts[posNum].riichiOffset.y;
				Rectangle current = { currentX, currentY,posConsts[posNum].height, posConsts[posNum].width };
				recs[i] = current;
			}
		}
	}

	
}

//void PlayerDiscardsLayout::selfDiscardsLayout(const Discards& discards)
//{
//	size = discards.getSize();
//	int riichiId = discards.getRiichiId();
//	if (riichiId == -1) {
//		for (int i = 0; i < size; i++) {
//			int row = i / TILES_IN_ROW;
//			int col = i % TILES_IN_ROW;
//			Rectangle current = { MY_PILE_POS.x + (col * TILE_WIDTH),
//				MY_PILE_POS.y + row * TILE_HEIGHT
//			,TILE_WIDTH, TILE_HEIGHT };
//			recs[i] = current;
//		}
//	}
//	else {
//		int riichiRow = riichiId / TILES_IN_ROW;
//		for (int i = 0; i < size; i++) {
//			int row = i / TILES_IN_ROW;
//			int col = i % TILES_IN_ROW;
//			if (i < riichiId || (i > riichiId && row != riichiRow)) {
//				Rectangle current = { MY_PILE_POS.x + (col * TILE_WIDTH),
//					MY_PILE_POS.y + row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
//				recs[i] = current;
//			}
//			else if (i > riichiId && (row  == riichiRow)) {
//				Rectangle current = { MY_PILE_POS.x + (col * TILE_WIDTH) - TILE_WIDTH + TILE_HEIGHT,
//					MY_PILE_POS.y + row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
//				recs[i] = current;
//			}
//			else if (i == riichiId) {
//				Rectangle current = { MY_PILE_POS.x + (col * TILE_WIDTH),
//					MY_PILE_POS.y + row * TILE_HEIGHT + TILE_HEIGHT - TILE_WIDTH
//				,TILE_HEIGHT, TILE_WIDTH };
//				recs[i] = current;
//			}
//		}
//	}
//}
//
//void PlayerDiscardsLayout::leftDiscardsLayout(const Discards& discards)
//{
//	size = discards.getSize();
//	int riichiId = discards.getRiichiId();
//	if (riichiId == -1) {
//		for (int i = 0; i < size; i++) {
//			int row = i / TILES_IN_ROW;
//			int col = i % TILES_IN_ROW;
//			Rectangle current = { LEFT_PILE_POS.x - (row * TILE_HEIGHT),LEFT_PILE_POS.y + (col * TILE_WIDTH),
//			TILE_HEIGHT,TILE_WIDTH };
//			recs[i] = current;
//		}
//	}
//	else {
//		int riichiRow = riichiId / TILES_IN_ROW;
//		for (int i = 0; i < size; i++) {
//			int row = i / TILES_IN_ROW;
//			int col = i % TILES_IN_ROW;
//			if (i < riichiId || (i > riichiId && row != riichiRow)) {
//				Rectangle current = { LEFT_PILE_POS.x - (row * TILE_HEIGHT),LEFT_PILE_POS.y + (col * TILE_WIDTH),
//				TILE_HEIGHT,TILE_WIDTH };
//				recs[i] = current;
//			}
//			else if (i > riichiId && (row == riichiRow)) {
//				Rectangle current = { LEFT_PILE_POS.x - (row * TILE_HEIGHT),
//					LEFT_PILE_POS.y + (col * TILE_WIDTH) - TILE_WIDTH + TILE_HEIGHT,
//				TILE_HEIGHT,TILE_WIDTH };
//				recs[i] = current;
//			}
//			else if (i == riichiId) {
//				Rectangle current = { LEFT_PILE_POS.x - (row * TILE_HEIGHT) - TILE_HEIGHT + TILE_WIDTH
//					,LEFT_PILE_POS.y + (col * TILE_WIDTH),
//				TILE_WIDTH,TILE_HEIGHT };
//				recs[i] = current;
//			}
//		}
//	}
//}
//
//void PlayerDiscardsLayout::rightDiscardsLayout(const Discards& discards)
//{
//	size = discards.getSize();
//	int riichiId = discards.getRiichiId();
//	if (riichiId == -1) {
//		for (int i = 0; i < size; i++) {
//			int row = i / TILES_IN_ROW;
//			int col = i % TILES_IN_ROW;
//			Rectangle current = { RIGHT_PILE_POS.x + (row * TILE_HEIGHT), RIGHT_PILE_POS.y - (col * TILE_WIDTH),
//			TILE_HEIGHT, TILE_WIDTH };
//			recs[i] = current;
//		}
//	}
//	else {
//		int riichiRow = riichiId / TILES_IN_ROW;
//		for (int i = 0; i < size; i++) {
//			int row = i / TILES_IN_ROW;
//			int col = i % TILES_IN_ROW;
//			if (i < riichiId || (i > riichiId && row != riichiRow)) {
//				Rectangle current = { RIGHT_PILE_POS.x + (row * TILE_HEIGHT), RIGHT_PILE_POS.y - (col * TILE_WIDTH),
//				TILE_HEIGHT, TILE_WIDTH };
//				recs[i] = current;
//			}
//			else if (i > riichiId && (row == riichiRow)) {
//				Rectangle current = { RIGHT_PILE_POS.x + (row * TILE_HEIGHT),
//					RIGHT_PILE_POS.y - (col * TILE_WIDTH) - TILE_HEIGHT + TILE_WIDTH,
//				TILE_HEIGHT, TILE_WIDTH };
//				recs[i] = current;
//			}
//			else if (i == riichiId) {
//				Rectangle current = { RIGHT_PILE_POS.x + (row * TILE_HEIGHT), RIGHT_PILE_POS.y - (col * TILE_WIDTH),
//				TILE_WIDTH, TILE_HEIGHT };
//				recs[i] = current;
//			}
//		}
//	}
//}
//
//void PlayerDiscardsLayout::topDiscardsLayout(const Discards& discards)
//{
//	size = discards.getSize();
//	int riichiId = discards.getRiichiId();
//	if (riichiId == -1) {
//		for (int i = 0; i < size; i++) {
//			int row = i / TILES_IN_ROW;
//			int col = i % TILES_IN_ROW;
//			Rectangle current = { TOP_PILE_POS.x - (col * TILE_WIDTH), TOP_PILE_POS.y - (row * TILE_HEIGHT),
//			TILE_WIDTH,TILE_HEIGHT };
//			recs[i] = current;
//		}
//	}
//	else {
//		int riichiRow = riichiId / TILES_IN_ROW;
//		for (int i = 0; i < size; i++) {
//			int row = i / TILES_IN_ROW;
//			int col = i % TILES_IN_ROW;
//			if (i < riichiId || (i > riichiId && row != riichiRow)) {
//				Rectangle current = { TOP_PILE_POS.x - (col * TILE_WIDTH), TOP_PILE_POS.y - (row * TILE_WIDTH),
//				TILE_WIDTH,TILE_HEIGHT };
//				recs[i] = current;
//			}
//			else if (i > riichiId && (row == riichiRow)) {
//				Rectangle current = { TOP_PILE_POS.x - (col * TILE_WIDTH) + TILE_HEIGHT - TILE_WIDTH
//					, TOP_PILE_POS.y - (row * TILE_WIDTH),
//				TILE_WIDTH,TILE_HEIGHT };
//				recs[i] = current;
//			}
//			else if (i == riichiId) {
//				Rectangle current = { TOP_PILE_POS.x - (col * TILE_WIDTH), TOP_PILE_POS.y - (row * TILE_WIDTH),
//				TILE_HEIGHT,TILE_WIDTH };
//				recs[i] = current;
//			}
//		}
//	}
//}
//
//void PlayerDiscardsLayout::ultimateDiscardsLayout(const Discards& discards, RelativePosition position)
//{
//	size = discards.getSize();
//	int posNum = static_cast<int>(position);
//	int riichiId = discards.getRiichiId();
//	if (riichiId == -1) {
//		for (int i = 0; i < size; i++) {
//			int row = i / TILES_IN_ROW;
//			int col = i % TILES_IN_ROW;
//			float currentX = posConsts[posNum].position.x + col * posConsts[posNum].colStep.x + row * posConsts[posNum].rowStep.x;
//			float currentY = posConsts[posNum].position.y + col * posConsts[posNum].colStep.y + row * posConsts[posNum].rowStep.y;
//			Rectangle current = { currentX, currentY, posConsts[posNum].width,posConsts[posNum].height };
//			recs[i] = current;
//		}
//	}
//	else {
//		int riichiRow = riichiId / TILES_IN_ROW;
//		for (int i = 0; i < size; i++) {
//			int row = i / TILES_IN_ROW;
//			int col = i % TILES_IN_ROW;
//			float currentX = posConsts[posNum].position.x + col * posConsts[posNum].colStep.x + row * posConsts[posNum].rowStep.x;
//			float currentY = posConsts[posNum].position.y + col * posConsts[posNum].colStep.y + row * posConsts[posNum].rowStep.y;
//			if (i < riichiId || (i > riichiId && row != riichiRow)) {
//				Rectangle current = { currentX, currentY, posConsts[posNum].width,posConsts[posNum].height };
//				recs[i] = current;
//			}
//			else if (i > riichiId && (row == riichiRow)) {
//				currentX += posConsts[posNum].afterRiichiShift.x;
//				currentY += posConsts[posNum].afterRiichiShift.y;
//				Rectangle current = { currentX, currentY, posConsts[posNum].width,posConsts[posNum].height };
//				recs[i] = current;
//			}
//			else if (i == riichiId) {
//				currentX += posConsts[posNum].riichiOffset.x;
//				currentY += posConsts[posNum].riichiOffset.y;
//				Rectangle current = { currentX, currentY,posConsts[posNum].height, posConsts[posNum].width };
//				recs[i] = current;
//			}
//		}
//	}
//}

RelativePosition GameDiscardsLayout::getRelativePosition(Wind perspective, Wind other)
{
	RelativePosition res = static_cast<RelativePosition>( (static_cast<int>(perspective)
		- static_cast<int>(other) + Constants::PLAYERS_NUM) % Constants::PLAYERS_NUM);
	return res;
}

GameDiscardsLayout::GameDiscardsLayout(const std::array<std::unique_ptr<Player>, Constants::PLAYERS_NUM>& players)
{
	for (int i = 0; i < Constants::PLAYERS_NUM; i++) {
		layouts[i] = PlayerDiscardsLayout(players[i]->getDiscards(),
				getRelativePosition(players[0]->getWind(), players[i]->getWind()));
	}

}

void GameDiscardsLayout::drawHitBoxes() const
{	
	for (const auto& layout : layouts) {
		for (int i = 0; i < layout.recs.size(); i++) {
			DrawRectangleLinesEx(layout.recs[i], 4.0f, GOLD);
		}
	}

	DrawCircleV(PlayerDiscardsLayout::MY_PILE_POS, 5.0f, RED);
	DrawCircleV(PlayerDiscardsLayout::RIGHT_PILE_POS, 5.0f, GREEN);
	DrawCircleV(PlayerDiscardsLayout::LEFT_PILE_POS, 5.0f, RED);
	DrawCircleV(PlayerDiscardsLayout::TOP_PILE_POS, 5.0f, RED);


}
