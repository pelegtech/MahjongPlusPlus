#include <algorithm>
#include <array>
#include <stdexcept>
#include "Hand.h"
#include "Kan.h"
#include "Meld.h"

//c'tor -----------------------------------------------------------------------
Hand::Hand(std::vector<Tile> tiles, std::vector<std::unique_ptr<Meld>> melds):
tiles(tiles),melds(std::move(melds)){}


//operators---------------------------------------------------------------------
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


std::ostream& operator<<(std::ostream& os, const Hand& hand) {
	os << "free tiles: " << std::endl;
	for (const auto& tile : hand.tiles) {
		os << "[" << tile.getName() << "] ";
	}
	os << std::endl << "melds: " << std::endl;
	for (const auto& meld : hand.melds) {
		os << meld->getContents() << std::endl;
	}
	return os;
}

//other methods ------------------------------------------


void Hand::sortHand() {
	std::sort(tiles.begin(), tiles.end());
}

void Hand::drawTile(const Tile& tile) {
	tiles.push_back(tile);
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
	if (index >= freeTilesNum() || index < 0) {
		throw Hand::illegalAcess();
	}
	discards.addTile(std::move(tiles[index]));
	tiles.erase(tiles.begin() + index);
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


void Hand::createAnkan(const Tile& t1) {

	//create the following copies of the first tile
	Tile t2(t1.getId() + 1);
	Tile t3(t1.getId() + 2);
	Tile t4(t1.getId() + 3);


	//find the iterators of the tiles in the hand vector
	std::vector<Tile>::iterator it1 = std::lower_bound(tiles.begin(), tiles.end(), t1);
	std::vector<Tile>::iterator it2 = std::lower_bound(tiles.begin(), tiles.end(), t2);
	std::vector<Tile>::iterator it3 = std::lower_bound(tiles.begin(), tiles.end(), t3);
	std::vector<Tile>::iterator it4 = std::lower_bound(tiles.begin(), tiles.end(), t4);


	//check if tiles were actually found
	if (it1 == tiles.end() || it1->getId() != t1.getId() ||
		it2 == tiles.end() || it2->getId() != t2.getId() ||
		it3 == tiles.end() || it3->getId() != t3.getId() ||
		it4 == tiles.end() || it4->getId() != t4.getId()) {
		throw tileNotFound();
	}


	//create ankan
	melds.push_back(std::make_unique<Ankan>(
		std::move(*it1),
		std::move(*it2),
		std::move(*it3),
		std::move(*it4)));

	//sort iterators and erase them by order
	std::array<std::vector<Tile>::iterator, 4> tempArr = { it1,it2,it3,it4 };
	std::sort(tempArr.begin(), tempArr.end());
	tiles.erase(tempArr[3]);
	tiles.erase(tempArr[2]);
	tiles.erase(tempArr[1]);
	tiles.erase(tempArr[0]);
}


void Hand::createDaiminkan(Discards& discardsPile,
	const Tile& t1, const Tile& t2, const Tile& t3,
	TileMarker marker) {
	
	//find given tiles in hand vector
	std::vector<Tile>::iterator it1 = std::lower_bound(tiles.begin(), tiles.end(), t1);
	std::vector<Tile>::iterator it2 = std::lower_bound(tiles.begin(), tiles.end(), t2);
	std::vector<Tile>::iterator it3 = std::lower_bound(tiles.begin(), tiles.end(), t3);

	//check if tiles were actually found
	if (it1 == tiles.end() || it1->getId() != t1.getId() ||
		it2 == tiles.end() || it2->getId() != t2.getId() ||
		it3 == tiles.end() || it3->getId() != t3.getId()) {
		throw tileNotFound();
	}

	//remove called tile from oponnent's discards
	Tile external = discardsPile.removeTile();

	//create daiminkan
	melds.push_back(std::make_unique<Daiminkan>(
		std::move(external),
		std::move(*it1),
		std::move(*it2),
		std::move(*it3),
		marker));

	//sort iterators and erase them by order
	std::array<std::vector<Tile>::iterator, 3> tempArr = { it1,it2,it3 };
	std::sort(tempArr.begin(), tempArr.end());
	tiles.erase(tempArr[2]);
	tiles.erase(tempArr[1]);
	tiles.erase(tempArr[0]);
}

void Hand::createShouminkan(const Tile& tile, int meldIndex) {
	if (meldIndex < 0 || meldIndex >= melds.size()) {
		throw meldNotFound();
	}
	std::vector<std::unique_ptr<Meld>>::iterator ponIt = (melds.begin() + meldIndex);
	std::vector<Tile>::iterator tileIt = std::lower_bound(tiles.begin(), tiles.end(), tile);
	if (tileIt == tiles.end() || tileIt->getId() != tile.getId()) {
		throw tileNotFound();
	}
	if (*ponIt == nullptr) {
		throw meldNotFound();
	}

	//take ownership of the meld
	std::unique_ptr<Meld> meld = std::move(*ponIt);

	//release the unique ptr to recast into pon unique ptr
	Meld* temp = meld.release();

	//recast it to unique ptr pon type
	std::unique_ptr<Pon> pon(static_cast<Pon*>(temp));

	//create the desired kan with the parameters
	auto kan = std::make_unique<Shouminkan>(std::move(*tileIt), std::move(pon));

	//put the new kan in place of the old pon
	*ponIt = std::move(kan);

	//clear the tile out of the free tiles
	tiles.erase(tileIt);
}

int Hand::freeTilesNum() const{
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




















