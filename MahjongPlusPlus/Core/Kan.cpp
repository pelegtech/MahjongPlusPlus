#include "Core/Kan.h"
#include "Core/Triplet.h"
#include "Core/Wall.h"

// kan functions:
Kan::Kan(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4, 
	TileMarker marker, MeldType type) :
	Meld(marker, type), tiles{ t1, t2, t3, t4 } {
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

bool Kan::containsDora(const Wall& wall) const
{
	for (int i = 0; i < KAN_SIZE; i++) {
		if (wall.isDora(tiles[i])){
			return true;
		}
	}
	return false;
}

Ankan::Ankan(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4) :
	Kan(t1, t2, t3, t4, TileMarker::SELF, MeldType::ANKAN) {
}

Daiminkan::Daiminkan(const Tile& externalTile, const Tile& tile2, const Tile& tile3, const Tile& tile4,
	TileMarker marker) : Kan(externalTile, tile2, tile3, tile4, marker, MeldType::DAIMINKAN) {
}

Shouminkan::Shouminkan(const Tile& ExternalTile, std::unique_ptr<Pon> pon) :Kan(
	ExternalTile, (*pon)[0], (*pon)[1], (*pon)[2], pon->getTileMarker(), MeldType::SHOUMINKAN) {
}

std::string Ankan::getContents() const {
	std::string res = "Daiminkan: ";
	for (int i = 0; i < this->size(); i++) {
		res += '[';
		res += (*this)[i].getName();
		if (i != this->size() - 1) {
			res += "], ";
		}
		else {
			res += "]";
		}
	}
	return res;
}

std::string Daiminkan::getContents() const {
	std::string res = "Daiminkan: ";
	switch (this->getTileMarker()) {
	case TileMarker::LEFT:
		res += ("/[" + (*this)[0].getName() + "]/"
			+ ", [" + (*this)[1].getName() + "], ["
			+ (*this)[2].getName() +"], ["
			+ (*this)[3].getName() + "]");
		break;
	case TileMarker::MIDDLE:
		res += ("[" + (*this)[0].getName() + "]"
			+ ", /[" + (*this)[1].getName() + "]/, ["
			+ (*this)[2].getName() +"], ["
			+ (*this)[3].getName() + "]");
		break;
	case TileMarker::RIGHT:
		res += ("[" + (*this)[0].getName() + "]" + 
			", [" + (*this)[1].getName() + "], ["
			+ (*this)[2].getName() + "], /[" 
			+ (*this)[3].getName() + "]/");
		break;
	}
	return res;
}

std::string Shouminkan::getContents() const {
	std::string res = "Shouminkan: ";
	switch (this->getTileMarker()) {
	case TileMarker::LEFT:
		res += ("/[" + (*this)[0].getName() + "]/"
			+ ", [" + (*this)[1].getName() + "], ["
			+ (*this)[2].getName() + "], ["
			+ (*this)[3].getName() + "]");
		break;
	case TileMarker::MIDDLE:
		res += ("[" + (*this)[0].getName() + "]"
			+ ", /[" + (*this)[1].getName() + "]/, ["
			+ (*this)[2].getName() + "], ["
			+ (*this)[3].getName() + "]");
		break;
	case TileMarker::RIGHT:
		res += ("[" + (*this)[0].getName() + "]" +
			", [" + (*this)[1].getName() + "], ["
			+ (*this)[2].getName() + "], /["
			+ (*this)[3].getName() + "]/");
		break;
	}
	return res;
}