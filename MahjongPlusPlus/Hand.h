#pragma once
#include "tile.h"
#include <string>
#include <vector>
#include <memory>
#include "Meld.h"
#include "Discards.h"

enum class KanType {
	Ankan,
	Daiminkan,
	Shouminkan
};

class Hand {

private:
	std::vector<Tile> tiles;
	std::vector<std::unique_ptr<Meld>> melds;
	static constexpr int MELD_SIZE = 3;
	static constexpr int MAX_HAND_SIZE = 14;
public:
	int handSize() const; //counts kan as 3 tiles
	const Tile& operator[](int index) const; //read only
	void addTile(const Tile& tile);
	void pon(Discards& discardsPile,
		std::vector<Tile>::iterator it1,
		std::vector<Tile>::iterator it2, TileMarker marker);
	void chi(Discards& discardsPile, std::vector<Tile>::iterator it1,
		std::vector<Tile>::iterator it2, TileMarker marker);
	void kan(Discards& discardsPile, std::vector<Tile>::iterator it1,
		std::vector<Tile>::iterator it2, std::vector<Tile>::iterator it3,
		TileMarker marker, KanType, std::vector<Tile>::iterator it4 = {});
};