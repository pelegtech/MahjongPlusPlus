#include "Hand.h"
int Hand::handSize() const{
	int counter = tiles.size();
	for (const auto& meld : melds) {
		counter += MELD_SIZE;
	}
	return counter;
}

const Tile& Hand::operator[](int index) const {
	if (index < 0 || index > MAX_HAND_SIZE - 1) {
		throw std::out_of_range("tried to reach a hand index out of bounds");
	}
	if (index < tiles.size()) {
		return tiles[index];
	}
	else {
		int newIndex = index - tiles.size();
		int i = 0;
		while (index > 4) {
			newIndex = newIndex - 
		}
	}
}
void addTile(const Tile& tile);
void pon(Discards& discardsPile,
	std::vector<Tile>::iterator it1,
	std::vector<Tile>::iterator it2, TileMarker marker);
void chi(Discards& discardsPile, std::vector<Tile>::iterator it1,
	std::vector<Tile>::iterator it2, TileMarker marker);
void kan(Discards& discardsPile, std::vector<Tile>::iterator it1,
	std::vector<Tile>::iterator it2, std::vector<Tile>::iterator it3,
	TileMarker marker, KanType, std::vector<Tile>::iterator it4 = {});