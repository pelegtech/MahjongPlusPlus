#include "Meld.h"
//meld functions:
Meld::Meld(TileMarker marker): marker(marker){}

TileMarker Meld::getTileMarker() const{
	return marker;
}

std::ostream& operator<<(std::ostream& os, const Meld& meld) {
	os << meld.getContents();
	return os;
}

//triplet functions:
Triplet::Triplet(const Tile& externalTile, const Tile& tile2, const Tile& tile3, TileMarker marker) : Meld(marker)
, tiles{ externalTile,tile2,tile3 } {

}
int Triplet::size() const {
	return Meld::TRIPLET_SIZE;
}
const Tile& Triplet::operator[](int index) const {
	if (index < 0 || index > 2) {
		throw std::invalid_argument("Triplet index out of bounds");
	}
	return tiles[index];
}

//pon functions:
Pon::Pon(const Tile& externalTile, const Tile& tile2, const Tile& tile3, TileMarker marker) :
	Triplet(externalTile, tile2, tile3, marker) {
	if (!isPon(externalTile, tile2, tile3)) {
		throw notPon();
	}
}

bool Pon::isPon(const Tile& t1, const Tile& t2, const Tile& t3) {
	if (Tile::isEqual(t1, t2) && Tile::isEqual(t1, t3)) {
		return true;
	}
	return false;
}

std::string Pon::getContents() const {
	std::string res = "Pon: ";
	int i = 0;
	for (; i < this->size() - 1; i++) {
		res += (*this)[i].getName();
		res += ", ";
	}
	res += (*this)[i].getName();
	return res;
}

//chi functions:
Chi::Chi(const Tile& externalTile, const Tile& tile2, const Tile& tile3, TileMarker marker):
	Triplet(externalTile, tile2, tile3, marker) {
	if (!isChi(externalTile, tile2, tile3)) {
		throw notChi();
	}
}

bool Chi::isChi(const Tile& t1, const Tile& t2, const Tile& t3) {
	if (t1.getSuit() != t2.getSuit() || t1.getSuit() != t3.getSuit()) {
		return false;
	}
	Tile a = t1, b = t2, c = t3;
	if (b < a) {
		std::swap(a, b);
	}
	if (c < b) {
		std::swap(b, c);
	}
	if (b < a) {
		std::swap(a, b);
	}
	if (c.getValue() - b.getValue() != 1 || b.getValue() - a.getValue() != 1) {
		return false;
	}
	return true;
}

std::string Pon::getContents() const {
	std::string res = "Chi: ";
	int i = 0;
	for (; i < this->size() - 1; i++) {
		res += (*this)[i].getName();
		res += ", ";
	}
	res += (*this)[i].getName();
	return res;
}


// kan functions:
Kan::Kan(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4, TileMarker marker):
	Meld(marker), tiles{ t1, t2, t3, t4 } {
	if (!isKan(t1, t2, t3, t4)) {
		throw notKan();
	}
}

int Kan::size() const {
	return Meld::KAN_SIZE;
}

const Tile& Kan::operator[](int index) const {
	return tiles[index];
}

bool Kan::isKan(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4) {
	if (Tile::isEqual(t1, t2) && Tile::isEqual(t1, t3) && Tile::isEqual(t1, t4)) {
		return true;
	}
	return false;
}

Ankan::Ankan(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4):
	Kan(t1,t2,t3,t4,TileMarker::SELF){}

Daiminkan::Daiminkan(const Tile& externalTile, const Tile& tile2, const Tile& tile3, const Tile& tile4,
	TileMarker marker): Kan(externalTile,tile2,tile3,tile4,marker){}

Shouminkan::Shouminkan(const Tile& ExternalTile,std::unique_ptr<Pon> pon) :
	Kan(ExternalTile, (*pon)[0], (*pon)[1], (*pon)[2], pon->getTileMarker()){ }

std::string Kan::getContents() const{
	std::string res = "Kan: ";
	int i = 0;
	for (; i < this->size() - 1; i++) {
		res += tiles[i].getName();
		res += ", ";
	}
	res += tiles[i].getName();
	return res;
}