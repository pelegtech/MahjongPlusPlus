#include "Core/Discards.h"
#include "Core/Tile.h"

Discards::Discards(): riichiTileId(UNDECIDED) {}

void Discards::addTile(const Tile& tile) {
	tiles.push_back(tile);
}

Tile Discards::removeTile() {
	if (tiles.empty()) {
		throw emptyDiscardsPile();
	}
	Tile res = std::move(tiles.back());
	tiles.pop_back();
	return res;
}

void Discards::riichi() {
	riichiTileId = static_cast<int>(tiles.size()) - 1;
}

int Discards::getRiichiId() const
{
	return riichiTileId;
}

int Discards::getSize() const
{
	return tiles.size();
}

const Tile& Discards::getLastDiscard() const
{
	return tiles.back();
}

Discards::ConstIterator::ConstIterator(const Tile* tile) : tile(tile) {}

const Tile& Discards::ConstIterator::operator*() const {
	return *tile;
}

Discards::ConstIterator& Discards::ConstIterator::operator++() {
	tile++;
	return *this;
}

bool Discards::ConstIterator::operator!=(const ConstIterator& other) const {
	return (tile != other.tile);
}

Discards::ConstIterator Discards::begin() const {
	return Discards::ConstIterator(tiles.data());
}

Discards::ConstIterator Discards::end() const {
	return Discards::ConstIterator(tiles.data() + tiles.size());
}
