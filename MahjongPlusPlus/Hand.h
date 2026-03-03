#pragma once
#include "tile.h"
#include <string>
#include <vector>
#include <memory>
#include "Meld.h"
class Hand {

private:
	std::vector<Tile> tiles;
	std::vector<std::unique_ptr<Meld>> melds;
public:
	int handSize();
	const Tile& operator[](int index);
	void addTile(const Tile& tile);

};