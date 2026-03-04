#include "Discards.h"

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

