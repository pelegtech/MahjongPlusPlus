#include "Core/Wall.h"
#include "Debug/Debug.h"


Wall::Wall():doraNum(1), tail(Tile::TOTAL_TILES_NUM - 1), head(0){
	//reserve space for vectors and initiate the tiles in sequence order
	wall.reserve(Tile::TOTAL_TILES_NUM);
	deadWall.reserve(DEAD_WALL_SIZE);
	for (int i = 0; i < Tile::TOTAL_TILES_NUM; i++) {
		wall.emplace_back(i);
	}

	//wall shuffle using std functions
	std::random_device randomNumber;
	std::mt19937 randomizer(randomNumber());
	std::shuffle(wall.begin(), wall.end(), randomizer);

	//copy the last 14 tiles from the wall to the dead wall
	for (int i = 0; i < DEAD_WALL_SIZE; i++) {
		deadWall.push_back(wall[head]);
		head++;
	}
	doras[0] = calcDora(doraIndicator(0));
}

Wall::Wall(const std::vector<Tile>& tiles) :doraNum(1), tail(Tile::TOTAL_TILES_NUM - 1), head(0), wall(tiles)
{
	if (tiles.size() != Constants::TOTAL_TILES_NUM) {
		throw invalidWallSize();
	}
	deadWall.reserve(DEAD_WALL_SIZE);
	for (int i = 0; i < DEAD_WALL_SIZE; i++) {
		deadWall.push_back(wall[head]);
		head++;
	}
	doras[0] = calcDora(doraIndicator(0));

}

int Wall::tilesLeft() const{
	return tail - head + 1;
}

const Tile& Wall::draw() {
	if (tilesLeft() <= 0) {
 		throw emptyWall();
	}
	int resId = tail;
	tail--;
	Log::add(wall[resId].getName());
	return wall[resId];
}

int Wall::addedKanCount() const{
	return doraNum - 1;
}

Tile Wall::kanDraw() {
	if (tilesLeft() <= 0) {
		throw emptyWall();
	}
	int currentkanDrawId = KAN_DRAW_ID + addedKanCount();
	Tile res = deadWall[currentkanDrawId];
	deadWall[currentkanDrawId] = wall[head++];
	return res;
}

void Wall::addDora() {
	doras[doraNum] = calcDora(doraIndicator(doraNum));
	doraNum++;
}

const Tile& Wall::doraIndicator(int index) const{
	if (index >= doraNum || index < 0) {
		throw invalidDora();
	}
	return deadWall[DORA_ID + index];
}

const Tile& Wall::uraDoraIndicator(int index) const{
	if (index >= doraNum || index < 0) {
		throw invalidUraDora();
	}
	return deadWall[URA_ID + index];
}

int Wall::getDoraNum() const
{
	return doraNum;
}

Tile Wall::calcDora(const Tile& indicator) const
{	
	if (indicator.getId() == Tile::EMPTY_TILE_ID) {
		throw Tile::InvalidTileID();
	}
	Tile res;
	//case of normal suit tile
	if (indicator.getSuit() != Suit::HONOR) {
		res = Tile::tileFromSpecs(indicator.getSuit(), ((((indicator.getValue() - 1) + 1) % 9) + 1), 0);
	}
	//case of dragon honor tile
	else if (indicator.getValue() >= 1 && indicator.getValue() <= 3) {
		res = Tile::tileFromSpecs(indicator.getSuit(), ((((indicator.getValue() - 1) + 1) % 3) + 1), 0);
	}
	//case of wind honor tile
	else if (indicator.getValue() >= 4 && indicator.getValue() <= 7) {
		res = Tile::tileFromSpecs(indicator.getSuit(), ((((indicator.getValue() - 4) + 1) % 4) + 4), 0);
	}
	return res;
}

const Tile& Wall::getDora(int index) const
{
	return doras[index];
}

bool Wall::isDora(const Tile& tile) const
{
	if (tile.isAkadora()) {
		return true;
	}
	for (int i = 0; i < doraNum; i++) {
		if (Tile::isEqual(tile, doras[i])) {
			return true;
		}
	}
	return false;
}

const std::vector<Tile>& Wall::getWallVector() const
{
	return wall;
}

const std::vector<Tile> Wall::getDeadWallVector() const
{
	return deadWall;
}

const int Wall::getHead() const
{
	return head;
}

const int Wall::getTail() const
{
	return tail;
}




//ConstIterator class:
Wall::ConstIterator::ConstIterator(const Tile* tile): tile(tile) {}

const Tile& Wall::ConstIterator::operator*() const {
	return *tile;
}
Wall::ConstIterator& Wall::ConstIterator::operator++() {
	tile++;
	return *this;
}
bool Wall::ConstIterator::operator!=(const ConstIterator& other) const {
	return (tile != other.tile);
}

Wall::ConstIterator Wall::begin() const {
	return Wall::ConstIterator(&wall[head]);
}
Wall::ConstIterator Wall::end() const {
	return Wall::ConstIterator((& wall[tail]) + 1);
}
