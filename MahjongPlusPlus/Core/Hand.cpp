#include "Core/Hand.h"
#include "Core/Kan.h"
#include "Core/Meld.h"
#include <exception>
#include <array>
#include <algorithm>



Hand::Hand()
{
	handTilesNum = 0;
}

Hand::Hand(std::array<Tile, MAX_HAND_TILES_NUM> handTiles): handTiles(handTiles)
{
	handTilesNum = MAX_HAND_TILES_NUM;
}

//c'tor -----------------------------------------------------------------------
Hand::Hand(std::vector<Tile> tiles, std::vector<std::unique_ptr<Meld>> melds) : melds(std::move(melds))
{
	for (int i = 0; i < tiles.size(); i++) {
		handTiles[i] = tiles[i];
	}
	handTilesNum = tiles.size();
}




std::string Hand::handToString() const
{
	std::string res = "free tiles: \n";
	for (int i = 0; i < handTilesNum; i++) {
		res += ("[" + handTiles[i].getName() + "] ");
	}
	res += "\nmelds:\n";
	for (const auto& meld : melds) {
		res += meld->getContents() + "\n";
	}
	return res;
}


std::ostream& operator<<(std::ostream& os, const Hand& hand) {
	os << "free tiles: " << std::endl;
	for (int i = 0; i < hand.handTilesNum; i++) {
		os << "[" << hand.handTiles[i].getName() << "] ";
	}
	os << std::endl << "melds: " << std::endl;
	for (const auto& meld : hand.melds) {
		os << meld->getContents() << std::endl;
	}
	return os;
}

//other methods ------------------------------------------


void Hand::sortHand() {
	std::sort(handTiles.begin(), handTiles.begin() + handTilesNum);
}

void Hand::drawTile(const Tile& tile) {
	drawnTile = tile;
}

void Hand::discardDrawnTile(Discards& discards) {
	if (drawnTile.getId() == Tile::EMPTY_TILE_ID) {
		throw notHoldingDrawnTile();
	}
	discards.addTile(drawnTile);
	drawnTile = Tile();
}

void Hand::discardHandTile(Discards& discards, int index) {
	if (handTilesNum == 0) {
		throw handIsEmpty();
	}
	if (index >= handTilesNum || index < 0) {
		throw Hand::illegalAcess();
	}
	//case of last tile just remove it.
	discards.addTile(handTiles[index]);
	if (index == MAX_HAND_TILES_NUM - 1) {
		handTiles[index] = Tile();
	}
	//case of middle tile we shift the entire array left by one tile.
	else {
		std::move(handTiles.begin() + index + 1, handTiles.begin() + handTilesNum, handTiles.begin() + index);
	}
	handTilesNum--;
}

void Hand::addDrawnTile() {
	if (handTilesNum == MAX_HAND_SIZE) {
		throw handIsFull();
	}
	if (drawnTile.getId() == Tile::EMPTY_TILE_ID) {
		throw notHoldingDrawnTile();
	}
	//we use binary search to insert in a sorted manner. afterwards we shift the array right and insert it.
	auto first = handTiles.begin();
	auto last = handTiles.begin() + handTilesNum;
	auto res = std::lower_bound(first, last, drawnTile);
	std::move_backward(res, last, last + 1);
	*(res) = drawnTile;
	drawnTile = Tile();
	handTilesNum++;
}


void Hand::createAnkanDrawn() {

	if (drawnTile.getId() == Tile::EMPTY_TILE_ID) {
		throw notHoldingDrawnTile();
	}

	//create the following copies of the first tile
	int id = drawnTile.getId();
	Tile t2((id + 1) % 4 + 4 * (id / 4));
	Tile t3((id + 2) % 4 + 4 * (id / 4));
	Tile t4((id + 3) % 4 + 4 * (id / 4));


	//find the iterators of the tiles in the hand vector
	auto first = handTiles.begin();
	auto last = handTiles.begin() + handTilesNum;
	auto it2 = std::lower_bound(first, last, t2);
	auto it3 = std::lower_bound(first, last, t3);
	auto it4 = std::lower_bound(first, last, t4);


	//check if tiles were actually found
	if (it2 == last || it2->getId() != t2.getId() ||
		it3 == last || it3->getId() != t3.getId() ||
		it4 == last || it4->getId() != t4.getId()) {
		throw tileNotFound();
	}


	//create ankan
	melds.push_back(std::make_unique<Ankan>(drawnTile, t2, t3, t4));
	drawnTile = Tile();

	//remove tiles from hand 
	auto it = std::max({ it2,it3,it4 });
	std::move(it + 1, last, it - 2);
	handTilesNum -= 3;
}

void Hand::createAnkanHand(const Tile& tile)
{
	//create the following copies of the first tile
	Tile t2 = Tile::getDiffCopy(tile, 1);
	Tile t3 = Tile::getDiffCopy(tile, 2);
	Tile t4 = Tile::getDiffCopy(tile, 3);
	
	

	//find the iterators of the tiles in the hand vector
	auto first = handTiles.begin();
	auto last = handTiles.begin() + handTilesNum;
	auto it1 = std::lower_bound(first, last, tile);
	auto it2 = std::lower_bound(first, last, t2);
	auto it3 = std::lower_bound(first, last, t3);
	auto it4 = std::lower_bound(first, last, t4);

	//check if tiles were actually found
	if (it1 == last || it1->getId() != tile.getId() ||
		it2 == last || it2->getId() != t2.getId() ||
		it3 == last || it3->getId() != t3.getId() ||
		it4 == last || it4->getId() != t4.getId()) {
		throw tileNotFound();
	}

	//create ankan
	melds.push_back(std::make_unique<Ankan>(tile, t2, t3, t4));

	//remove tiles from hand 

	auto it = std::max({ it1,it2,it3,it4 });
	std::move(it + 1, last, it - 3);
	handTilesNum -= Kan::KAN_SIZE;
}


void Hand::createDaiminkan(Discards& discardsPile,
	const Tile& t1, const Tile& t2, const Tile& t3,
	TileMarker marker) {
	
	//find given tiles in hand vector
	auto first = handTiles.begin();
	auto last = handTiles.begin() + handTilesNum;
	auto it1 = std::lower_bound(first, last, t1);
	auto it2 = std::lower_bound(first, last, t2);
	auto it3 = std::lower_bound(first, last, t3);

	//check if tiles were actually found
	if (it1 == last || it1->getId() != t1.getId() ||
		it2 == last || it2->getId() != t2.getId() ||
		it3 == last || it3->getId() != t3.getId()) {
		throw tileNotFound();
	}

	//remove called tile from oponnent's discards
	Tile external = discardsPile.removeTile();

	//create daiminkan
	melds.push_back(std::make_unique<Daiminkan>(external,t1,t2,t3,marker));

	//remove tiles from hand
	auto it = std::max({ it1,it2,it3 });
	std::move(it + 1, last, it - 2);
	handTilesNum -= 3;
}

void Hand::createShouminkanDrawn() {

	if (drawnTile.getId() == Tile::EMPTY_TILE_ID) {
		throw notHoldingDrawnTile();
	}

	int meldIndex = -1;
	for (int i = 0; i < melds.size(); i++) {
		if (melds[i]->getMeldType() == MeldType::PON) {
			if (drawnTile.getSuit() == (*melds[i])[0].getSuit() && drawnTile.getValue() == (*melds[i])[0].getValue()) {
				meldIndex = i;
				break;
			}
		}
	}

	if (meldIndex == -1) {
		throw meldNotFound();
	}

	

	//take ownership of the meld
	std::unique_ptr<Meld> meld = std::move(melds[meldIndex]);

	//release the unique ptr to recast into pon unique ptr
	Meld* temp = meld.release();

	//recast it to unique ptr pon type
	std::unique_ptr<Pon> pon(static_cast<Pon*>(temp));

	//create the desired kan with the parameters
	auto kan = std::make_unique<Shouminkan>(drawnTile, std::move(pon));
	drawnTile = Tile();

	//put the new kan in place of the old pon
	melds[meldIndex] = std::move(kan);
}

void Hand::createShouminkanHand(const Tile& tile)
{
	int meldIndex = -1;
	for (int i = 0; i < melds.size(); i++) {
		if (melds[i]->getMeldType() == MeldType::PON) {
			if (tile.getSuit() == (*melds[i])[0].getSuit() && tile.getValue() == (*melds[i])[0].getValue()) {
				meldIndex = i;
				break;
			}
		}
	}

	if (meldIndex == -1) {
		throw meldNotFound();
	}

	auto tileIt = std::lower_bound(handTiles.begin(), handTiles.begin() + handTilesNum, tile);
	if (tileIt == handTiles.begin() + handTilesNum || tileIt->getId() != tile.getId()) {
		throw tileNotFound();
	}

	//take ownership of the meld
	std::unique_ptr<Meld> meld = std::move(melds[meldIndex]);

	//release the unique ptr to recast into pon unique ptr
	Meld* temp = meld.release();

	//recast it to unique ptr pon type
	std::unique_ptr<Pon> pon(static_cast<Pon*>(temp));

	//create the desired kan with the parameters
	auto kan = std::make_unique<Shouminkan>(std::move(*tileIt), std::move(pon));

	//put the new kan in place of the old pon
	melds[meldIndex] = std::move(kan);

	//clear the tile out of the free tiles
	std::move(tileIt + 1, handTiles.begin() + handTilesNum, tileIt);
	handTilesNum--;
}



int Hand::freeTilesNum() const{
	int res = handTilesNum;
	if (drawnTile.getId() != Tile::EMPTY_TILE_ID) {
		res += 1;
	}
	return res;
}

int Hand::legalHandSize() const{
	
	int counter = handTilesNum;
	if (drawnTile.getId() != Tile::EMPTY_TILE_ID) {
		counter += 1;
	}
	for (const auto& meld : melds) {
		counter += Meld::TRIPLET_SIZE;
	}
	return counter;
}

int Hand::realHandSize() const {
	int counter = handTilesNum;
	if (drawnTile.getId() != Tile::EMPTY_TILE_ID) {
		counter += 1;
	}
	for (const auto& meld : melds) {
		counter += meld->size();
	}
	return counter;
}

const Tile& Hand::getDrawnTile() const
{
	return drawnTile;
}

bool Hand::isHoldingDrawnTile() const
{
	if (drawnTile.getId() != Tile::EMPTY_TILE_ID) {
		return true;
	}
	return false;
}

const Tile& Hand::getHandTile(int index) const
{
	if (index < 0 || index >= handTilesNum) {
		throw illegalAcess();
	}
	return handTiles[index];
}

const std::array<Tile, Hand::MAX_HAND_TILES_NUM>& Hand::getHandTiles() const
{
	return handTiles;
}

int Hand::getHandTilesNum() const
{
	return handTilesNum;
}


const std::vector<std::unique_ptr<Meld>>& Hand::getMelds() const
{
	return melds;
}

void Hand::addTile(const Tile& tile)
{
	if (handTilesNum == MAX_HAND_SIZE) {
		throw handIsFull();
	}
	
	//we use binary search to insert in a sorted manner. afterwards we shift the array right and insert it.
	auto first = handTiles.begin();
	auto last = handTiles.begin() + handTilesNum;
	auto res = std::lower_bound(first, last, tile);
	std::move_backward(res, last, last + 1);
	*(res) = tile;
	handTilesNum++;
}

bool Hand::isEmpty() const
{
	if (handTilesNum != 0) {
		return false;
	}
	if (melds.size() != 0) {
		return false;
	}
	return true;
}

bool Hand::isTileInHandTiles(const Tile& tile) const
{
	for (int i = 0; i < handTilesNum; i++) {
		if (tile.getId() == handTiles[i].getId()) {
			return true;
		}
	}
	return false;
}

std::vector<std::unique_ptr<HandShape>> Hand::getValidHands() const
{	
	std::vector<Tile> remainingTiles;
	bool flag = false;
	for (int i = 0; i < handTilesNum; i++) {
		if (handTiles[i].getId() > drawnTile.getId() && flag == false) {
			remainingTiles.push_back(drawnTile);
			flag = true;
		}
		remainingTiles.push_back(handTiles[i]);
	}
	if (flag == false) {
		remainingTiles.push_back(drawnTile);
	}
	std::vector<std::unique_ptr<HandShape>> shapes;
	standardShape currShape;
	if (!melds.empty()) {
		for (const auto& meld : melds) {
			MeldType type = meld->getMeldType();
			switch (type) {
			case MeldType::ANKAN: {
				BlockTriplet block((*meld)[0], (*meld)[1], (*meld)[2], (*meld)[3], BlockType::CLOSED_KAN);
				currShape.addTriplet(block);
				break;
			}
			case MeldType::DAIMINKAN:
			case MeldType::SHOUMINKAN: {
				BlockTriplet block((*meld)[0], (*meld)[1], (*meld)[2], (*meld)[3], BlockType::OPEN_KAN);
				currShape.addTriplet(block);
				break;
			}
			case MeldType::CHI: {
				BlockTriplet block((*meld)[0], (*meld)[1], (*meld)[2], (*meld)[3], BlockType::OPEN_SEQUENCE);
				currShape.addTriplet(block);
				break;
			}
			case MeldType::PON: {
				BlockTriplet block((*meld)[0], (*meld)[1], (*meld)[2], (*meld)[3], BlockType::OPEN_TRIPLET);
				currShape.addTriplet(block);
				break;
			}
			}
		}
	}
	else {
		sevenPairsShape currSevenPairsShape;
		validSevenPairs(shapes, currSevenPairsShape, remainingTiles);
		//same but for thirteen orphans
	} 
	validStandardHand(shapes, currShape, remainingTiles);
}

void validSevenPairs(std::vector<std::unique_ptr<HandShape>>& shapes,
	sevenPairsShape currShape, std::vector<Tile> remainingTiles) {
	int lastTileId = remainingTiles.size() - 1;
	if (remainingTiles.size() > 2) {
		if (Tile::isEqual(remainingTiles[lastTileId], remainingTiles[lastTileId - 2])) {
			return;
		}
	}
	if (Tile::isEqual(remainingTiles[lastTileId], remainingTiles[lastTileId - 1])) {
		currShape.addPair(BlockPair(remainingTiles[lastTileId - 1], remainingTiles[lastTileId]));
		remainingTiles.pop_back();
		remainingTiles.pop_back();
		if (remainingTiles.size() == 0) {
			shapes.push_back(std::make_unique<HandShape>(std::move(currShape)));
		}
		else {
			validSevenPairs(shapes, std::move(currShape), std::move(remainingTiles));
		}
	}
}

void validStandardHand(std::vector<std::unique_ptr<HandShape>>& shapes,
	standardShape currShape, std::vector<Tile> remainingTiles) {
	if (remainingTiles.size() == 2) {
		if (Tile::isEqual(remainingTiles[0], remainingTiles[1])) {
			currShape.addPair(BlockPair(remainingTiles[0], remainingTiles[1]));
			shapes.push_back(std::make_unique<HandShape>(std::move(currShape)));
		} 
		return;
	}
	if (remainingTiles.size() == 3) {
		Tile t1 = remainingTiles[0];
		Tile t2 = remainingTiles[1];
		Tile t3 = remainingTiles[2];
		if (Block::isTriplet(t1,t2,t3)) {
			currShape.addTriplet(BlockTriplet(t1, t2, t3, BlockType::CLOSED_TRIPLET));
			shapes.push_back(std::make_unique<HandShape>(std::move(currShape)));
		}
		else if (Block::isSequence(t1, t2, t3)) {
			currShape.addTriplet(BlockTriplet(t1, t2, t3, BlockType::CLOSED_SEQUENCE));
			shapes.push_back(std::make_unique<HandShape>(std::move(currShape)));
		}
		return;
	}
	int lastTileId = remainingTiles.size() - 1;
	Tile lastTile = remainingTiles[lastTileId];
	if (Block::isTriplet(remainingTiles[lastTileId - 2], remainingTiles[lastTileId - 1], lastTile)) {
		BlockTriplet block(remainingTiles[lastTileId - 2], remainingTiles[lastTileId - 1], lastTile, BlockType::CLOSED_TRIPLET);
		currShape.addTriplet(std::move(block));
		validStandardHand(shapes,currShape, std::vector<Tile>(remainingTiles.begin(), remainingTiles.end() - 3));
		currShape.popTriplet();
	} 
	if (lastTile.getSuit() != Suit::HONOR) {
		int currIndex = lastTileId - 1;
		int id1 = -1;
		int id2 = -1;

		while (currIndex >= 0) {
			if (remainingTiles[currIndex].getSuit() != lastTile.getSuit()) {
				break;
			}
			if (remainingTiles[currIndex].getValue() < lastTile.getValue() - 2) {
				break;
			}
			if (remainingTiles[currIndex].getValue() == lastTile.getValue()) {
				currIndex--;
				continue;
			}
			if (remainingTiles[currIndex].getValue() == lastTile.getValue() - 1) {
				id1 = currIndex--;
				continue;
			}
			if (remainingTiles[currIndex].getValue() == lastTile.getValue() - 2) {
				id2 = currIndex;
				break;
			}
		}
		if (id1 != -1 && id2 != -1) {
			BlockTriplet block(remainingTiles[id2], remainingTiles[id1], lastTile, BlockType::CLOSED_SEQUENCE);
			currShape.addTriplet(std::move(block));
			std::vector<Tile> newRemainingTiles(remainingTiles);
			newRemainingTiles.pop_back();
			newRemainingTiles.erase(newRemainingTiles.begin() + id1);
			newRemainingTiles.erase(newRemainingTiles.begin() + id2);
			validStandardHand(shapes, currShape,std::move(newRemainingTiles));
			currShape.popTriplet();
		}
	}
	if (Tile::isEqual(lastTile, remainingTiles[lastTileId - 1]) && currShape.getHasPair() == false) {
		currShape.addPair(BlockPair(lastTile, remainingTiles[lastTileId - 1]));
		validStandardHand(shapes, currShape, std::vector<Tile>(remainingTiles.begin(), remainingTiles.end() - 2));
		currShape.popPair();
	}
	return;
}







bool standardShape::getHasPair()
{
	return hasPair;
}

standardShape::standardShape() : tripletNum(0), hasPair(false)
{
}

void standardShape::popTriplet()
{
	triplets[--tripletNum] = BlockTriplet();
}

void standardShape::popPair()
{
	hasPair = false;
	pair = BlockPair();
}

void standardShape::addTriplet(const BlockTriplet& triplet)
{
	triplets[tripletNum++] = triplet;
}

void standardShape::addPair(const BlockPair& inputPair)
{
	if (hasPair) {
		throw alreadyHasPair();
	}
	hasPair = true;
	pair = inputPair;
}

sevenPairsShape::sevenPairsShape(): pairNum(0)
{
}

void sevenPairsShape::addPair(const BlockPair& pair)
{
	pairs[pairNum++] = pair;
}





