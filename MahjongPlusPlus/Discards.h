#pragma once
#include "Tile.h"
#include <vector>
#include <stdexcept>

class Discards {
private:
	static constexpr int UNDECIDED = -1;
	static constexpr int ROW_SIZE = 6;
	std::vector<Tile> tiles;
	int riichiTileId;
public:
	Discards();
	void addTile(const Tile& tile);
	Tile removeTile();

	//sets current last tile index to be the riichi tile
	void riichi();

	class emptyDiscardsPile : public std::exception {
		const char* what() const noexcept override {
			return "cannot make operation on an empty discards pile";
		}
	};
};