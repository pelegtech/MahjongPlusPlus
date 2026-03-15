#include "Core/Triplet.h"


//triplet functions:
Triplet::Triplet(const Tile& externalTile, const Tile& tile2, const Tile& tile3,
	TileMarker marker, MeldType type) : Meld(marker,type)
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
Pon::Pon(const Tile& externalTile, const Tile& tile2, const Tile& tile3,TileMarker marker) :
	Triplet(externalTile, tile2, tile3, marker,MeldType::PON) {
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
	switch (this->getTileMarker()) {
	case TileMarker::LEFT:
		res += ("/[" + (*this)[0].getName() + "]/"
			+ ", [" + (*this)[1].getName() + "], [" + (*this)[2].getName() + "]");
		break;
	case TileMarker::MIDDLE:
		res += ("[" + (*this)[0].getName() + "]"
			+ ", /[" + (*this)[1].getName() + "]/, [" + (*this)[2].getName() + "]");
		break;
	case TileMarker::RIGHT:
		res += ("[" + (*this)[0].getName() + "]"
			+ ", [" + (*this)[1].getName() + "], /[" + (*this)[2].getName() + "]/");
		break;
	}

	return res;
}

//chi functions:
Chi::Chi(const Tile& externalTile, const Tile& tile2, const Tile& tile3,TileMarker marker) :
	Triplet(externalTile, tile2, tile3, marker, MeldType::CHI) {
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

std::string Chi::getContents() const {
	std::string res = "Chi: ";
	switch (this->getTileMarker()) {
	case TileMarker::LEFT:
		res += ("/[" + (*this)[0].getName() + "]/"
			+ ", [" + (*this)[1].getName() + "], [" + (*this)[2].getName() + "]");
		break;
	case TileMarker::MIDDLE:
		res += ("[" + (*this)[1].getName() + "]"
			+ ", /[" + (*this)[0].getName() + "]/, [" + (*this)[2].getName() + "]");
		break;
	case TileMarker::RIGHT:
		res += ("[" + (*this)[1].getName() + "]"
			+ ", [" + (*this)[2].getName() + "], /[" + (*this)[0].getName() + "]/");
		break;
	}
	return res;
}