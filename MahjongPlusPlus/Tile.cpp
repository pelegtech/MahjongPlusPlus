#include "Tile.h"
#include <stdexcept>
//Ctor ----------------------------------------
Tile::Tile(int id) : id(id){
	if (id < 0 || id > TOTAL_TILES_NUM -1) {
		throw InvalidTileID();
	}
}

//operators -----------------------------------
bool Tile::operator<(const Tile& other) const {
	return this->id < other.id;
}

bool Tile::operator==(const Tile& other) const {
	return this->id == other.id;
}

std::ostream& operator<<(std::ostream& os, const Tile& tile) {
	os << "id= " << tile.getId() << " name: " << tile.getName() << " ";
	return os;
}

//methods --------------------------------------
Tile Tile::tileFromSpecs(Suit suit, int value, int copy){
	if (value > VALUES_IN_SUIT || value < 1) {
		throw InvalidTileValue();
	}
	if (suit == Suit::HONOR && value > HONORS_NUM) {
		throw InvalidTileValueHonor();
	}
	//first go into the correct range of suit, each suit has 36 tiles.
	//then add the value -1 (offset because we start at 0 and got to 135), multiply by the 
	// amount of copies each tile has (4)
	//add the given compy number (0-3).
	int id = ((static_cast<int>(suit) * VALUES_IN_SUIT * COPIES) + ((value - 1) * COPIES) + copy);
	Tile res = Tile(id);
	return res;
}

Tile Tile::honorTileFromSpecs(HonorType type, int copy) {
	Tile res = tileFromSpecs(Suit::HONOR, static_cast<int>(type), copy);
	return res;
}

bool Tile::isEqual(const Tile& tile1, const Tile& tile2) {
	return (tile1.getSuit() == tile2.getSuit() && tile1.getValue() == tile2.getValue());
}


//getters---------------------------------------------
int Tile::getId() const {
	return id;
}

Suit Tile::getSuit() const {
	return static_cast<Suit>(id / TILES_IN_SUIT);
}

int Tile::getValue() const {
	return ((id % (VALUES_IN_SUIT * COPIES)) / COPIES) + 1;
}

std::string Tile::getName() const {
	std::string suitName;
	std::string valueName;
	switch (this->getSuit()) {
	case Suit::MAN:
		suitName = "man";
		valueName = std::to_string(getValue());
		break;
	case Suit::PIN:
		suitName = "pin";
		valueName = std::to_string(getValue());
		break;
	case Suit::SOU:
		suitName = "sou";
		valueName = std::to_string(getValue());
		break;
	case Suit::HONOR:
		valueName = getHonorName();
		if (getValue() <= DRAGONS_NUM) {
			suitName = "dragon";
		}
		else {
			suitName = "wind";
		}
		break;
	}
	std::string result = valueName + " " + suitName;
	if (isAkadora() == true) {
		return "Red " + result;
	}
	else {
		return result;
	}
}

bool Tile::isAkadora() const {
	return (id == AKA_MAN || id == AKA_PIN || id == AKA_SOU);
}



//private methods -------------------------------------------------
std::string Tile::getHonorName() const {
	if (getSuit() != Suit::HONOR) {
		throw std::invalid_argument("Input tile is not an honor tile");
	}
	switch (this->getValue()) {
	case static_cast<int>(HonorType::WHITE_DRAGON):
		return  "White";
	case static_cast<int>(HonorType::GREEN_DRAGON):
		return  "Green";
	case static_cast<int>(HonorType::RED_DRAGON):
		return  "Red";
	case static_cast<int>(HonorType::EAST_WIND):
		return  "East";
	case static_cast<int>(HonorType::SOUTH_WIND):
		return  "South";
	case static_cast<int>(HonorType::WEST_WIND):
		return  "West";
	case static_cast<int>(HonorType::NORTH_WIND):
		return  "North";
	default:
		throw std::invalid_argument("something went wrong with getHonorName");
	}
}