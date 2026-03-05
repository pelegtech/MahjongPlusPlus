#include "Wall.h"

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

	//move the last 14 tiles from the wall to the dead wall
	for (int i = 0; i < DEAD_WALL_SIZE; i++) {
		deadWall.push_back(wall[head]);
		head++;
	}
}
int Wall::tilesLeft() const{
	return tail - head + 1;
}
Tile Wall::draw() {
	if (tilesLeft() <= 0) {
 		throw emptyWall();
	}
	
	return wall[tail--];
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
	doraNum++;
}
const Tile& Wall::dora(int index) const{
	if (index >= doraNum || index < 0) {
		throw invalidDora();
	}
	return deadWall[DORA_ID + index];
}
const Tile& Wall::uraDora(int index) const{
	if (index >= doraNum || index < 0) {
		throw invalidUraDora();
	}
	return deadWall[URA_ID + index];
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
