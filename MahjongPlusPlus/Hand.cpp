#include "Hand.h"

Hand::Hand(std::vector<Tile> tiles, std::vector<std::unique_ptr<Meld>> melds):
tiles(tiles),melds(std::move(melds)){}

int Hand::tilesNum() const{
	return static_cast<int>(tiles.size());
}

int Hand::legalHandSize() const{
	int counter = static_cast<int>(tiles.size());
	for (const auto& meld : melds) {
		counter += Meld::TRIPLET_SIZE;
	}
	return counter;
}

int Hand::realHandSize() const {
	int counter = static_cast<int>(tiles.size());
	for (const auto& meld : melds) {
		counter += meld->size();
	}
	return counter;
}

const Tile& Hand::lastTile() const {
	int id = static_cast<int>(tiles.size()) - 1;
	return (*this)[id];
}

const Tile& Hand::operator[](int index) const {
	if (index < 0 || index > MAX_HAND_SIZE - 1) {
		throw std::out_of_range("tried to reach a hand index out of bounds");
	}
	if (index < tiles.size()) {
		return tiles[index];
	}
	else {
		int currIndex = index - static_cast<int>(tiles.size());
		int i = 0;
		while (currIndex > melds[i]->size() - 1) {
			currIndex = currIndex - melds[i]->size();
			i++;
		}
		return (*melds[i])[currIndex];
	}
}



void Hand::drawTile(const Tile& tile) {
	tiles.push_back(tile);
}
void Hand::addDrawnTile() {
	if (tiles.empty()) {
		throw handIsEmpty();
	}
	Tile temp = std::move(tiles.back());
	tiles.pop_back();
	auto it1 = tiles.begin();
	auto it2 = tiles.end();
	auto res = std::lower_bound(it1, it2, temp);
	tiles.insert(res, std::move(temp));
}
void Hand::discardDrawnTile(Discards& discards) {
	if (tiles.empty()) {
		throw handIsEmpty();
	}
	discards.addTile(std::move(tiles.back()));
	tiles.pop_back();
}
void Hand::discardHandTile(Discards& discards, int index) {
	if (tiles.empty()) {
		throw handIsEmpty();
	}
	if (index >= tilesNum() || index < 0) {
		throw Hand::illegalAcess();
	}
	discards.addTile(std::move(tiles[index]));
	tiles.erase(tiles.begin() + index);
}




void Hand::createAnkan(std::vector<Tile>::iterator it1,
	std::vector<Tile>::iterator it2,
	std::vector<Tile>::iterator it3,
	std::vector<Tile>::iterator it4) {
	melds.push_back(std::make_unique<Ankan>(
		std::move(*it1),
		std::move(*it2),
		std::move(*it3),
		std::move(*it4)));
	std::array<std::vector<Tile>::iterator, 4> tempArr = { it1,it2,it3,it4 };
	std::sort(tempArr.begin(),tempArr.end());
	tiles.erase(tempArr[3]);
	tiles.erase(tempArr[2]);
	tiles.erase(tempArr[1]);
	tiles.erase(tempArr[0]);
}

void Hand::createDaiminkan(Discards& discardsPile,
	std::vector<Tile>::iterator it1,
	std::vector<Tile>::iterator it2,
	std::vector<Tile>::iterator it3,
	TileMarker marker) {
	Tile external = discardsPile.removeTile();
	melds.push_back(std::make_unique<Daiminkan>(
		std::move(external), 
		std::move(*it1),
		std::move(*it2),
		std::move(*it3),
		marker));
	std::array<std::vector<Tile>::iterator, 3> tempArr = { it1,it2,it3};
	std::sort(tempArr.begin(), tempArr.end());
	tiles.erase(tempArr[2]);
	tiles.erase(tempArr[1]);
	tiles.erase(tempArr[0]);
}

void Hand::createShouminkan(std::vector<Tile>::iterator tileIt,
	std::vector<std::unique_ptr<Meld>>::iterator ponIt) {
	//releases original unique_ptr and makes a new one for a pon type
	std::unique_ptr<Pon> pon(static_cast<Pon*>(ponIt->release()));
	auto kan = std::make_unique<Shouminkan>(std::move(*tileIt),std::move(pon));
	*ponIt = std::move(kan);
	tiles.erase(tileIt);
}

void Hand::sortHand() {
	std::sort(tiles.begin(), tiles.end());
}

//debug functions -----

std::ostream& operator<<(std::ostream& os, const Hand& hand) {
	os << "free tiles: " << std::endl;
	for (const auto& tile : hand.tiles) {
		os << "["<< tile.getName() << "] ";
	}
	os << std::endl << "melds: " << std::endl;
	for (const auto& meld : hand.melds) {
		os << meld->getContents() << std::endl;
	}
	return os;
}
